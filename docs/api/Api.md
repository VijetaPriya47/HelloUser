# Api

The `Api` class manages WebSocket setup, authentication, and sending JSON-RPC payloads to the exchange.

## Header
```cpp
#include "Api.hpp"
```

## Public Interface
```cpp
// Constructors
Api();
Api(const std::string &client_id, const std::string &client_secret);

// Destructor
~Api();

// Methods
[[nodiscard]] std::pair<int, std::string> api_public(const std::string &msg);
[[nodiscard]] std::pair<int, std::string> api_private(const std::string &msg);
[[nodiscard]] int Authenticate();
```

- **api_public(msg)**: Sends a JSON-RPC request to a public endpoint.
- **api_private(msg)**: Sends a JSON-RPC request to a private (authenticated) endpoint.
- **Authenticate()**: Builds an auth payload using the configured `client_id` and `client_secret`, sends it, and returns a status code (`0` for success).

## Behavior & Lifecycle
- On construction, `Api` prompts for a WebSocket implementation (Boost or ZSocket/websocketpp), switches to WebSocket mode, and calls `Authenticate()`.
- The default constructor uses built-in demo credentials; the parameterized constructor uses provided credentials.

## Return Values
All request methods return `std::pair<int, std::string>`:
- `first`: status code (0 success, non-zero indicates failure)
- `second`: raw JSON response body

## Examples

### 1) Default credentials (guest) and a public call
```cpp
#include <iostream>
#include "Api.hpp"

int main() {
    Api api; // prompts for socket choice, authenticates immediately

    const std::string payload = R"({
        "jsonrpc": "2.0",
        "id": 1,
        "method": "public/get_order_book",
        "params": {"instrument_name": "ETH-PERPETUAL", "depth": 10}
    })";

    auto [status, body] = api.api_public(payload);
    if (status == 0) std::cout << body << "\n";
}
```

### 2) Custom credentials and a private call (place limit order)
```cpp
#include <iostream>
#include "Api.hpp"

int main() {
    Api api{"<CLIENT_ID>", "<CLIENT_SECRET>"}; // prompts for socket choice, authenticates with your creds

    const std::string buy_limit = R"({
        "jsonrpc": "2.0",
        "method": "private/buy",
        "params": {"instrument_name": "ETH-PERPETUAL", "type": "limit", "price": 3500.5, "amount": 10},
        "id": 2
    })";

    auto [status, body] = api.api_private(buy_limit);
    if (status != 0) {
        std::cerr << "Request failed: " << body << "\n";
    }
}
```

## Notes
- The constructor reads from `std::cin` to decide the socket implementation. For non-interactive usage, consider refactoring to inject the socket type programmatically.
- Host and port are defined by the socket (`test.deribit.com:443`).