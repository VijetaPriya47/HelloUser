#pragma once
#include <nlohmann/json.hpp>
#include <bits/stdc++.h>

#include "Func.hpp"
#include "Spdlog.hpp"
#include "User.hpp"
#include "Json.hpp"
#include "Api.hpp"

int process_cancel_order(const std::function<std::pair<int, std::string>(std::string)> &action);
int process_place_order(const std::function<std::pair<int, std::string>(std::string, double, int)> &action);
int process_modify_order(const std::function<std::pair<int, std::string>(std::string, double, int)> &action);
int process_order_book(const std::function<std::pair<int, std::string>(std::string, int)> &action);
int process_view_position(const std::function<std::pair<int, std::string>(std::string)> &action);
int process_open_orders(const std::function<std::pair<int, std::string>(std::string)> &action);
int process_market_data(const std::function<std::pair<int, std::string>(std::string, int)> &action);
