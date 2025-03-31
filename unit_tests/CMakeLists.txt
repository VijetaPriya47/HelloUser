cmake_minimum_required(VERSION 3.10)
project(SpdlogHelloWorld)

set(CMAKE_CXX_STANDARD 17)

# Include spdlog
find_package(spdlog REQUIRED)

# Add the executable
add_executable(hello_log spdlog.cpp)
target_link_libraries(hello_log spdlog::spdlog)
