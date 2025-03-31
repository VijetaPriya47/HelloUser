#include "Api.hpp"
#include <iostream>

// Default constructor for guest mode
Api::Api() : m_client_id("9XMzjE7H"), m_client_secret("zvR4snVF_jaUlOZwdoPKbiVehBLCCO7xHgNEUlZrNg4")
{
    std::cout << "Guest mode activated with predefined client ID and secret.\n";

    // Prompt user to select socket type
    initialize_socket();

    // Switch to WebSockets
    m_socket->switch_to_ws();

    // Authenticate
    int status = Authenticate();
    if (status)
    {
        std::cout << "Authentication failed!\n";
        return;
    }
    else
    {
        std::cout << "Authentication Successful!\n";
    }
}

// Constructor for custom credentials
Api::Api(const std::string &client_id, const std::string &client_secret)
    : m_client_id(client_id), m_client_secret(client_secret)
{
    std::cout << "Custom credentials mode activated.\n";

    // Prompt user to select socket type
    initialize_socket();

    // Switch to WebSockets
    m_socket->switch_to_ws();

    // Authenticate
    int status = Authenticate();
    if (status)
    {
        std::cout << "Authentication failed!\n";
        return;
    }
    else
    {
        std::cout << "Authentication Successful!\n";
    }
}

// Destructor
Api::~Api()
{
    std::cout << "Destroying Api Instance\n";
    delete m_socket;
}

// Generate the authentication message dynamically
std::string Api::generate_auth_msg() const
{
    return R"({
        "jsonrpc": "2.0",
        "id": 9929,
        "method": "public/auth",
        "params": {
            "grant_type": "client_credentials",
            "client_id": ")" +
           m_client_id + R"(",
            "client_secret": ")" +
           m_client_secret + R"("
        }
    })";
}

[[nodiscard]] std::pair<int, std::string> Api::api_public(const std::string &message)
{
    auto resp = m_socket->ws_request(message);
    return resp;
}

[[nodiscard]] std::pair<int, std::string> Api::api_private(const std::string &message)
{
    auto resp = m_socket->ws_request(message);
    return resp;
}

// Example Authenticate method
[[nodiscard]] int Api::Authenticate()
{
    std::string auth_msg = generate_auth_msg();
    std::cout << "Authenticating with client ID: " << m_client_id << "\n";
    std::pair<int, std::string> pr = api_private(auth_msg);

    return pr.first;
}

// Initialize the socket based on user choice
void Api::initialize_socket()
{
    std::cout << "Select Socket Implementation:\n";
    std::cout << "1) Boost\n";
    std::cout << "2) ZSocket\n";
    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        std::cout << "Using Boost Socket Implementation.\n";
        m_socket = new BSocket();
    }
    else if (choice == 2)
    {
        std::cout << "Using ZSocket Implementation.\n";
        m_socket = new Socketpp();
    }
    else
    {
        std::cerr << "Invalid choice. Defaulting to ZSocket.\n";
        m_socket = new Socketpp();
    }
}
