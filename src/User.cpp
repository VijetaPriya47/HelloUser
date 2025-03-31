#include "User.hpp"
#include "Websockets/Socket.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#include <numeric>
#include <vector>

using namespace std;

/**
 * @brief Construct a new User:: User object
 *
 */

User::User()
{
    //---------------Logger Initilization------------------

    // Ensure the logs directory exists
    if (!std::filesystem::exists("logs"))
    {
        std::filesystem::create_directory("logs");
    }

    // Set up the logger for JSON responses
    auto json_logger = spdlog::basic_logger_mt("json_logger", "logs/json_responses.log", true);
    spdlog::set_default_logger(json_logger);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] %v");

    // Configure automatic flushing after every log entry
    spdlog::flush_on(spdlog::level::info);

    spdlog::info("Logger initialized successfully.");
    std::cout << "Logger initialized successfully.\n";

    //---------------Logger Initilization------------------

    std::cout << "\n-- New API Instance Created --\n";

    // Prompt user for mode selection
    std::cout << "Select Authentication Mode:\n";
    std::cout << "1) Guest Access\n";
    std::cout << "2) Custom Credentials\n";
    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        m_api = new Api(); // Uses default constructor
        std::cout << "Guest access enabled with default client ID and secret.\n";
    }
    else if (choice == 2)
    {
        std::string client_id, client_secret;
        std::cout << "Enter Client ID: ";
        std::cin >> client_id;
        std::cout << "Enter Client Secret: ";
        std::cin >> client_secret;
        m_api = new Api(client_id, client_secret); // Uses parameterized constructor
        std::cout << "Custom credentials enabled.\n";
    }
    else
    {
        std::cerr << "Invalid selection. Exiting application.\n";
        exit(1);
    }
}

/**
 * @brief Trading Dashboard
 *
 *
 *
 */

void User::Start()
{
    std::cout << "\n-- Application Running --\n";
    bool run = true;

    while (run)
    {
        system("clear");

        std::cout << "\n=========================================\n"
                  << "             TRADING DASHBOARD           \n"
                  << "=========================================\n"
                  << " [1] -> Place New Order                  \n"
                  << " [2] -> Cancel Existing Order            \n"
                  << " [3] -> Modify Existing Order            \n"
                  << " [4] -> View Order Book                  \n"
                  << " [5] -> Check Open Positions             \n"
                  << " [6] -> Live Market Data Streaming       \n"
                  << " [7] -> View All Open Orders             \n"
                  << " [8] -> Exit Application                 \n"
                  << "=========================================\n"
                  << "-> Please select an option: ";

        int inp;
        std::cin >> inp;

        if (std::cin.fail() || inp < 1 || inp > 8)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n!! Invalid Input! Please select a valid option (1-8).\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        auto start_time = chrono::high_resolution_clock::now();
        switch (inp)
        {
        case 1:
        {
            int status = process_place_order([this](const std::string &inst, double price, int quant)
                                             { return place_order(inst, price, quant); });
            std::cout << (status ? "!! Failed to place the order.\n" : ">> Order placed successfully!\n");
            break;
        }

        case 2:
        {
            int status = process_cancel_order([this](const std::string &order_id)
                                              { return cancel_order(order_id); });
            std::cout << (status ? "!! Failed to cancel the order.\n" : ">> Order cancelled successfully!\n");
            break;
        }

        case 3:
        {
            int status = process_modify_order([this](const std::string &order_id, double price, int quant)
                                              { return modify_order(order_id, price, quant); });
            std::cout << (status ? "!! Failed to modify the order.\n" : ">> Order modified successfully!\n");
            break;
        }

        case 4:
        {
            int status = process_order_book([this](const std::string &inst, int depth)
                                            { return get_orderbook(inst, depth); });
            std::cout << (status ? "!! Failed to fetch the order book.\n" : ">> Order book retrieved successfully!\n");
            break;
        }

        case 5:
        {
            int status = process_view_position([this](const std::string &inst)
                                               { return view_position(inst); });
            std::cout << (status ? "!! Failed to retrieve positions.\n" : ">> Positions fetched successfully!\n");
            break;
        }

        case 6:
        {
            int status = process_market_data([this](const std::string &kind, int type)
                                             { return get_marketdata(kind, type); });
            std::cout << (status ? "!! Failed to fetch market data.\n" : ">> Market data streaming started successfully!\n");
            break;
        }

        case 7:
        {
            int status = process_open_orders([this](const std::string &kind)
                                             { return get_openorders(kind); });
            std::cout << (status ? "!! Failed to retrieve open orders.\n" : ">> Open orders fetched successfully!\n");
            break;
        }

        case 8:
        {
            run = false;
            std::cout << "\n>> Exiting application... Goodbye!\n";

            break;
        }
        }

        auto end_time = chrono::high_resolution_clock::now();
        double latency = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
        trading_loop_latencies.push_back(latency); // Store latency
        std::cout << "End-to-end trading loop latency: " << latency << " ms\n";

        if (run)
        {
            std::cout << "\n-> Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}

/**
 * @brief It diplays all the mean latencies in the program
 *
 */

void User::display_mean_latencies()
{
    auto calculate_mean = [](const std::vector<double> &latencies) -> double
    {
        if (latencies.empty())
            return 0.0;
        double sum = std::accumulate(latencies.begin(), latencies.end(), 0.0);
        return sum / latencies.size();
    };

    std::cout << "\n--- Mean Latencies ---\n";
    std::cout << "Order Placement Latency: " << calculate_mean(order_latencies) << " ms\n";
    std::cout << "Market Data Processing Latency: " << calculate_mean(market_data_latencies) << " ms\n";
    std::cout << "WebSocket Message Propagation Delay: " << calculate_mean(order_latencies) << " ms\n";
    std::cout << "End-to-End Trading Loop Latency: " << calculate_mean(trading_loop_latencies) << " ms\n";
}
