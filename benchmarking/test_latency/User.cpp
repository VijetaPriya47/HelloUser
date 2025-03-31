#include "User.hpp"
#include <fstream>
#include <chrono>
#include <vector>
#include <iostream>
#include <thread>
#include <sys/resource.h> // For memory usage
#include <sys/time.h>     // For CPU usage


User::User() : m_api(new Api()) {}

User::~User() {
    delete m_api;
}


// User::User()
// {
//     std::cout << "\n-- New API Instance Created --\n";

//         m_api = new Api(); 
//         std::cout << "Guest access enabled with default client ID and secret.\n";


// }


std::pair<int, std::string> User::place_order(const std::string& inst, double price, int quant) {

    std::ostringstream payload;
	payload << R"({
        	"jsonrpc": "2.0",
        	"method": "private/buy",
        	"params": {
            		"instrument_name": ")"
			<< inst << R"(",
            		"type": "limit",
            		"price": )"
			<< price << R"(,
            		"amount": )"
			<< quant << R"(
        	},
        	"id": "1"
    	})";

	std::string payload_str = payload.str();
	return m_api->api_private(payload_str);
}

void User::benchmark_place_order(int iterations) {
    std::vector<double> response_times;
    std::vector<double> cpu_usages;
    std::vector<double> memory_usages;

    for (int i = 0; i < iterations; ++i) {
      
        auto start_time = std::chrono::high_resolution_clock::now();


        auto [status, response] = place_order("BTC-PERPETUAL", 12.0, 50);
        // std::cout<<response;

        std::cout<<"Placed\n";


        auto end_time = std::chrono::high_resolution_clock::now();
        double response_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        response_times.push_back(response_time);

        // Measure CPU usage
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        double cpu_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1e6; // User CPU time in seconds
        cpu_usages.push_back(cpu_time);

        // Measure memory usage
        std::ifstream status_file("/proc/self/status");
        std::string line;
        double memory_usage = 0.0;
        while (std::getline(status_file, line)) {
            if (line.find("VmRSS:") != std::string::npos) { // Resident Set Size (RSS)
                memory_usage = std::stod(line.substr(line.find_last_of('\t') + 1)) / 1024.0; // Convert to MB
                break;
            }
        }
        memory_usages.push_back(memory_usage);

        // Optional: Sleep to simulate real-world conditions
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Write metrics to a CSV file
    std::ofstream csv_file("benchmark_results.csv");
    csv_file << "Iteration,ResponseTime(ms),CPUUsage(s),MemoryUsage(MB)\n";
    for (int i = 0; i < iterations; ++i) {
        csv_file << i + 1 << "," << response_times[i] << "," << cpu_usages[i] << "," << memory_usages[i] << "\n";
    }
    csv_file.close();

    std::cout << "Benchmark completed. Results saved to benchmark_results.csv\n";
}