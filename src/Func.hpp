#include <bits/stdc++.h>
#include "User.hpp"
#include "Params.hpp"
#include "Json.hpp"
#include "Api.hpp"
#include "Spdlog.hpp"

#include <nlohmann/json.hpp>

using namespace std;

std::pair<int, std::string> place_order(const std::string &, double, int);
std::pair<int, std::string> cancel_order(const std::string &);
std::pair<int, std::string> modify_order(const std::string &, double, int);
std::pair<int, std::string> get_orderbook(const std::string &, int);
std::pair<int, std::string> view_position(const std::string &);
std::pair<int, std::string> get_openorders(const std::string &);
std::pair<int, std::string> get_marketdata(const std::string &, int);