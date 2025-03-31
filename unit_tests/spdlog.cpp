#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <iostream>

int main() {
    // Create a logger that writes to a file
    auto logger = spdlog::basic_logger_mt("file_logger", "logs/hello_world.log");

    // Set logger as the default
    spdlog::set_default_logger(logger);

    // Set log level to INFO
    spdlog::set_level(spdlog::level::info);

    // Write "Hello, World!" to the log file
    spdlog::info("Hello, World!");

    // Flush the log to make sure it is written to the file
    spdlog::default_logger()->flush();

    std::cout << "Log written to logs/hello_world.log" << std::endl;

    return 0;
}
