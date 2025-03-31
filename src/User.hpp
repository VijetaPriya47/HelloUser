#pragma once
#include "Func.hpp"
#include "Spdlog.hpp"
#include "Params.hpp"
#include "Json.hpp"
#include "Api.hpp"
#include <nlohmann/json.hpp>
#include <vector>

using namespace std;

class User
{
public:
    User();
    void Start();

    std::pair<int, std::string> place_order(const std::string &, double, int);
    std::pair<int, std::string> cancel_order(const std::string &);
    std::pair<int, std::string> modify_order(const std::string &, double, int);
    std::pair<int, std::string> get_orderbook(const std::string &, int);
    std::pair<int, std::string> view_position(const std::string &);
    std::pair<int, std::string> get_openorders(const std::string &);
    std::pair<int, std::string> get_marketdata(const std::string &, int);

    int display_response(const std::string &resp);
    int process_cancel_order(const function<pair<int, string>(string)> &action);
    int process_place_order(const function<pair<int, string>(string, double, int)> &action);
    int process_modify_order(const function<pair<int, string>(string, double, int)> &action);
    int process_order_book(const function<pair<int, string>(string, int)> &action);
    int process_view_position(const function<pair<int, string>(string)> &action);
    int process_open_orders(const function<pair<int, string>(string)> &action);
    int process_market_data(const function<pair<int, string>(string, int)> &action);

    void display_mean_latencies();

private:
    Api *m_api;
    std::vector<double> order_latencies;
    std::vector<double> market_data_latencies;
    std::vector<double> websocket_latencies;
    std::vector<double> trading_loop_latencies;
};