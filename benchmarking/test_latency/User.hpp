#pragma once
#include <string>
#include <utility>
#include <Api.hpp>

class User {
public:
    User();
    ~User();

    // Benchmarking method for place order
    void benchmark_place_order(int iterations);

    // Place order function (moved from Func.cpp)
    std::pair<int, std::string> place_order(const std::string& inst, double price, int quant);

private:
    Api *m_api;
};