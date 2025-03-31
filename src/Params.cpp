#include "Params.hpp"
#include <chrono>

using namespace std;


int User::process_place_order(const std::function<std::pair<int, std::string>(std::string, double, int)> &action)
{
    try
    {
        std::string instrument;
        double price = 0.0;
        int quantity = 0;

        std::cout << "Instrument (e.g., BTC-PERPETUAL, ETH-PERPETUAL): ";
        std::cin >> instrument;

        std::cout << "Price: ";
        std::cin >> price;

        std::cout << "Quantity: ";
        std::cin >> quantity;

        auto start_time = std::chrono::high_resolution_clock::now(); // Start timer
        auto [status, response] = action(instrument, price, quantity);
        auto end_time = std::chrono::high_resolution_clock::now(); // End timer

        double latency = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        order_latencies.push_back(latency); // Store latency
        std::cout << "Order placement latency: " << latency << " ms\n";

        return status | display_response(response);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception occurred: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}

int User::process_cancel_order(const std::function<std::pair<int, std::string>(std::string)> &action)
{
    try
    {
        std::string order_id;

        std::cout << "Enter Order ID: ";
        std::cin >> order_id;

        auto [status, response] = action(order_id);

        return status | display_response(response);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}

int User::process_modify_order(const std::function<std::pair<int, std::string>(std::string, double, int)> &action)
{
    try
    {
        std::string order_id;
        double price = 0.0;
        int quantity = 0;

        std::cout << "Order ID: ";
        std::cin >> order_id;

        std::cout << "New Price: ";
        std::cin >> price;

        std::cout << "New Quantity: ";
        std::cin >> quantity;

        auto [status, response] = action(order_id, price, quantity);

        return status | display_response(response);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}

int User::process_view_position(const std::function<std::pair<int, std::string>(std::string)> &action)
{
    try
    {
        std::string instrument;

        std::cout << "Instrument (e.g., ETH-PERPETUAL): ";
        cin >> instrument;

        auto [status, response] = action(instrument);

        return status | display_response(response);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}

int User::process_order_book(const std::function<std::pair<int, std::string>(std::string, int)> &action)
{
    try
    {
        std::string instrument;
        int depth = 0;

        std::cout << "Instrument (e.g., BTC-PERPETUAL): ";
        std::cin >> instrument;

        std::cout << "Depth: ";
        std::cin >> depth;

        auto [status, response] = action(instrument, depth);

        return status | display_response(response);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}

int User::process_open_orders(const std::function<std::pair<int, std::string>(std::string)> &action)
{
    try
    {
        std::string kind;

        std::cout << "Kind (e.g., null, future, option): ";
        std::getline(std::cin >> std::ws, kind);

        auto [status, response] = action(kind);

        return status | display_response(response);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}

int User::process_market_data(const std::function<std::pair<int, std::string>(std::string, int)> &action)
{
    try
    {
        std::cout << "[1] Subscribe to symbol\n"
                  << "[2] Unsubscribe from symbol\n"
                  << "[3] Orderbook of symbols\n"
                  << "[4] Back\n";

        int option = 0;
        std::cin >> option;

        if (option < 1 || option > 4)
        {
            throw std::invalid_argument("Invalid Input\n");
        }

        std::string channel;
        int count = 0;

        switch (option)
        {
        case 1:
            std::cout << "Enter channel to subscribe (e.g., book.ETH-PERPETUAL.100ms): ";
            std::cin >> channel;
            break;

        case 2:
            std::cout << "Enter channel to unsubscribe (e.g., user.lock): ";
            std::cin >> channel;
            break;

        case 3:
            std::cout << "Enter number of announcements [1, 50]: ";
            std::cin >> count;
            channel = std::to_string(count);
            break;

        case 4:
            return EXIT_SUCCESS;
        }

        auto start_time = std::chrono::high_resolution_clock::now(); // Start timer
        auto [status, response] = action(channel, option);
        auto end_time = std::chrono::high_resolution_clock::now(); // End timer

        double latency = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        market_data_latencies.push_back(latency); // Store latency
        // std::cout << "Market data processing latency: " << latency << " ms\n";

        return status | display_response(response);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}
