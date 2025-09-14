# User

The `User` class provides an interactive dashboard and a set of convenience methods that construct JSON-RPC payloads and delegate to `Api`.

## Header
```cpp
#include "User.hpp"
```

## Public Interface
```cpp
User();
void Start();

std::pair<int, std::string> place_order(const std::string &instrument, double price, int quantity);
std::pair<int, std::string> cancel_order(const std::string &order_id);
std::pair<int, std::string> modify_order(const std::string &order_id, double price, int quantity);
std::pair<int, std::string> get_orderbook(const std::string &instrument, int depth);
std::pair<int, std::string> view_position(const std::string &instrument);
std::pair<int, std::string> get_openorders(const std::string &kind);
std::pair<int, std::string> get_marketdata(const std::string &channel, int type);

int display_response(const std::string &resp);

int process_cancel_order(const std::function<std::pair<int, std::string>(std::string)> &action);
int process_place_order(const std::function<std::pair<int, std::string>(std::string, double, int)> &action);
int process_modify_order(const std::function<std::pair<int, std::string>(std::string, double, int)> &action);
int process_order_book(const std::function<std::pair<int, std::string>(std::string, int)> &action);
int process_view_position(const std::function<std::pair<int, std::string>(std::string)> &action);
int process_open_orders(const std::function<std::pair<int, std::string>(std::string)> &action);
int process_market_data(const std::function<std::pair<int, std::string>(std::string, int)> &action);

void display_mean_latencies();
```

## Behavior
- The constructor sets up logging to `logs/json_responses.log` and prompts for authentication mode (guest or custom credentials). It then creates `Api`, which asks for socket implementation and authenticates.
- `Start()` presents a menu loop for common trading operations.
- `display_response()` parses JSON using `nlohmann::json`, logs via `spdlog`, and prints either `result` or the full JSON.

## Return Values
All operation methods return `std::pair<int, std::string>`:
- `first`: status code (0 success)
- `second`: raw JSON response

The `process_*` helpers perform input collection and timing, invoke the provided action, and combine status with `display_response()`.

## Examples

### 1) Interactive dashboard
```cpp
#include "User.hpp"

int main() {
    User user;    // prompts for auth mode and config
    user.Start(); // interactive menu
    user.display_mean_latencies();
}
```

### 2) Programmatic use of convenience methods
Note: current constructors prompt for input. For fully non-interactive workflows, adapt constructors to accept configuration without `std::cin`.
```cpp
#include <iostream>
#include "User.hpp"

int main() {
    User user;

    auto [s1, r1] = user.place_order("ETH-PERPETUAL", 3500.5, 10);
    if (s1) std::cerr << "place_order failed: " << r1 << "\n";

    auto [s2, r2] = user.get_orderbook("ETH-PERPETUAL", 10);
    if (!s2) std::cout << r2 << "\n";
}
```

## Latencies
`display_mean_latencies()` reports mean values for:
- Order placement latency
- Market data processing latency
- WebSocket propagation delay
- End-to-end trading loop latency