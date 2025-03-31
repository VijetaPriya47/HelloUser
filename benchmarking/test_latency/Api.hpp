#pragma once
#include "Json.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include "Websockets/Socket.hpp"
#include "Websockets/zsocket.hpp"
#include "Websockets/boost.hpp"


#include <string>
#include <thread>
#include <atomic>

class Api
{
public:
    // Constructor
    Api();
    Api(const std::string &client_id, const std::string &client_secret);

    // Destructor
    ~Api();

    // Methods
    [[nodiscard]] std::pair<int, std::string> api_public(const std::string &msg);
    [[nodiscard]] std::pair<int, std::string> api_private(const std::string &msg);

    [[nodiscard]] int Authenticate();

private:
    Socket *m_socket;
    std::string m_client_id;
    std::string m_client_secret;

    std::string generate_auth_msg() const;
    void initialize_socket(); // Add this declaration
};
