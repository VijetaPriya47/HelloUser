#include "zsocket.hpp"
#include <chrono>
#include <iostream>

// Latency measuring is there dor Web Socket Propagation Delay

static context_ptr on_tls_init()
{
	// establishes a SSL connection
	context_ptr ctx = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23);

	try
	{
		ctx->set_options(boost::asio::ssl::context::default_workarounds |
						 boost::asio::ssl::context::no_sslv2 |
						 boost::asio::ssl::context::no_sslv3 |
						 boost::asio::ssl::context::single_dh_use);
	}
	catch (std::exception &e)
	{
		std::cout << "Error in context pointer: " << e.what() << std::endl;
	}
	return ctx;
}

// Destructor
Socketpp::~Socketpp()
{
	// Close the WebSocket connection
	try
	{
		websocketpp::lib::error_code ec;
		auto metadata = con_metadata;
		m_endpoint.stop_perpetual();
		m_ws->join();
		m_endpoint.close(metadata->m_hdl, websocketpp::close::status::normal, "", ec);
		if (ec)
		{
			std::cout << "> Error initiating close: " << ec.message() << '\n';
			return;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error during WebSocket close: " << e.what() << '\n';
	}
}

// Constructor
Socketpp::Socketpp()
{
	m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
	m_endpoint.clear_error_channels(websocketpp::log::elevel::all);
	m_endpoint.clear_access_channels(websocketpp::log::alevel::frame_payload);

	m_endpoint.init_asio();
	m_endpoint.set_tls_init_handler(bind(&on_tls_init));
	m_endpoint.start_perpetual();

	m_ws.reset(new websocketpp::lib::thread(&client::run, &m_endpoint));
	std::cout << "Socketpp Intialized!\n";
}

[[nodiscard]] std::pair<int, std::string> Socketpp::ws_request(const std::string& message) {
    websocketpp::lib::error_code ec;

    // Start measuring time
    auto start_time = std::chrono::high_resolution_clock::now();

    // Send the WebSocket message
    m_endpoint.send(con_metadata->m_hdl, message, websocketpp::frame::opcode::text, ec);
    if (ec) {
        std::cerr << "Error sending message: " << ec.message() << std::endl;
        return std::make_pair(1, ec.message());
    }

    // Wait for the response
    std::unique_lock<std::mutex> lock(con_metadata->m_mutex);
    con_metadata->m_cv.wait(lock, [&]() { return !con_metadata->msg_queue.empty(); });

    // End measuring time
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate latency
    double latency = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "WebSocket message propagation delay: " << latency << " ms\n";

    // // Update the latency vector in the User class
    // if (user) {
    //     user->add_websocket_latency(latency);
    // }

    // Get the response
    std::string response = con_metadata->msg_queue.back();
    con_metadata->msg_queue.pop_back();

    return std::make_pair(0, response);
}

void Socketpp::switch_to_ws()
{
	// Perform the websocket handshake
	websocketpp::lib::error_code ec;

	std::string protocol = "wss://";
	std::string uri = protocol + host + "/ws/api/v2";
	client::connection_ptr con = m_endpoint.get_connection(uri, ec);

	if (ec)
	{
		std::cout << "> Connect initialization error: " << ec.message() << '\n';
		std::cout << uri << '\n';
		return;
	}
	connection_metadata::ptr metadata_ptr(new connection_metadata(1, con->get_handle(), uri));
	con_metadata = metadata_ptr;

	con->set_open_handler(websocketpp::lib::bind(
		&connection_metadata::on_open,
		metadata_ptr,
		&m_endpoint,
		websocketpp::lib::placeholders::_1));
	con->set_fail_handler(websocketpp::lib::bind(
		&connection_metadata::on_fail,
		metadata_ptr,
		&m_endpoint,
		websocketpp::lib::placeholders::_1));

	con->set_message_handler(websocketpp::lib::bind(
		&connection_metadata::on_message,
		metadata_ptr,
		websocketpp::lib::placeholders::_1,
		websocketpp::lib::placeholders::_2));

	m_endpoint.connect(con);
	std::cout << "Waiting for connection\n";
	while (con_metadata->m_status == "Connecting")
		sleep(1);
	std::cout << "Moved to WebSocket Connection\n";
}
