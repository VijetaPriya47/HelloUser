#include "User.hpp"
#include <iostream>

void start_benchmarking(User& user) {
    std::cout << "Do you want to start benchmarking? (yes/no): ";
    std::string input;
    std::cin >> input;

    if (input == "yes" || input == "y") {
        std::cout << "Starting benchmarking...\n";
        user.benchmark_place_order(100); // Run the benchmark for 10,000 iterations
        std::cout << "Benchmarking complete. Results saved to 'benchmark_results.csv'.\n";
    } else {
        std::cout << "Benchmarking canceled.\n";
    }
}

int main() {
    User user = User();

    // Ask the user to start benchmarking
    start_benchmarking(user);

    return 0;
}