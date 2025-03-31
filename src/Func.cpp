#include "Func.hpp"

using namespace std;

// Function responsible for placing order
std::pair<int, std::string> User::place_order(const std::string &inst, double price, int quant)
{
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

// Function responsible for canclling order
std::pair<int, std::string> User::cancel_order(const std::string &order_id)
{
	std::ostringstream payload;
	payload << R"({
        	"jsonrpc": "2.0",
        	"method": "private/cancel",
        	"params": {
            		"order_id": ")"
			<< order_id << R"("
        	},
        	"id": "2"
    	})";

	std::string payload_str = payload.str();
	return m_api->api_private(payload_str);
}

// Function responsible for modifing order
std::pair<int, std::string> User::modify_order(const std::string &order_id, double price, int quant)
{
	std::ostringstream payload;
	payload << R"({
        	"jsonrpc": "2.0",
        	"method": "private/edit",
        	"params": {
            		"order_id": ")"
			<< order_id << R"(",
            		"price": )"
			<< price << R"(,
            		"amount": )"
			<< quant << R"(
        	},
        	"id": "3"
    	})";

	std::string payload_str = payload.str();
	return m_api->api_private(payload_str);
}

// Function responsible for fetching order book
std::pair<int, std::string> User::get_orderbook(const std::string &inst, int depth)
{
	std::ostringstream payload;
	payload << R"({
        	"jsonrpc": "2.0",
        	"method": "public/get_order_book",
        	"params": {
            		"instrument_name": ")"
			<< inst << R"(",
			"depth": )"
			<< depth << R"(
        	},
        	"id": "4"
    	})";

	std::string payload_str = payload.str();
	return m_api->api_public(payload_str);
}

// Function to View our current position
std::pair<int, std::string> User::view_position(const std::string &inst)
{
	std::ostringstream payload;
	payload << R"({
        	"jsonrpc": "2.0",
        	"method": "private/get_position",
        	"params": {
            		"instrument_name": ")"
			<< inst << R"("
        	},
        	"id": "5"
    	})";

	std::string payload_str = payload.str();
	return m_api->api_private(payload_str);
}

// Function to View open orders
std::pair<int, std::string> User::get_openorders(const std::string &kind)
{
	std::ostringstream payload;
	if (kind == "null")
	{
		payload << R"({
        		"jsonrpc": "2.0",
        		"method": "private/get_open_orders",
        		"params": {
        		},
        		"id": "6"
    		})";
	}
	else
	{
		payload << R"({
        		"jsonrpc": "2.0",
        		"method": "private/get_open_orders",
        		"params": {
            			"kind": ")"
				<< kind << R"(",
				"type": "all"
        		},
        		"id": "6"
    		})";
	}

	std::string payload_str = payload.str();
	return m_api->api_private(payload_str);
}

// Function to View Market data
std::pair<int, std::string> User::get_marketdata(const std::string &channel, int type)
{
	std::ostringstream payload;
	if (type == 1)
	{
		payload << R"({
        		"jsonrpc": "2.0",
        		"method": "private/subscribe",
        		"params": {
            			"channels": [")"
				<< channel << R"("]
        		},
        		"id": "7"
    		})";
	}
	else if (type == 2)
	{
		payload << R"({
        		"jsonrpc": "2.0",
        		"method": "private/unsubscribe",
        		"params": {
            			"channels": [")"
				<< channel << R"("]
        		},
        		"id": "8"
    		})";
	}
	else
	{
		payload << R"({
        		"jsonrpc": "2.0",
        		"method": "public/get_announcements",
        		"params": {
            			"count": )"
				<< std::stoi(channel) << R"(
        		},
        		"id": "9"
    		})";
	}
	std::string payload_str = payload.str();
	return m_api->api_private(payload_str);
	// return m_api -> api_market(payload_str);
}
