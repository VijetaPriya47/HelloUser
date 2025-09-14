# Examples

## 1) Public: Order Book
```cpp
#include "Api.hpp"

int main() {
    Api api; // choose socket, authenticates
    const std::string payload = R"({
        "jsonrpc": "2.0",
        "id": 1,
        "method": "public/get_order_book",
        "params": {"instrument_name": "BTC-PERPETUAL", "depth": 5}
    })";
    auto [status, body] = api.api_public(payload);
}
```

## 2) Private: Buy Limit Order
```cpp
#include "Api.hpp"

int main() {
    Api api{"<CLIENT_ID>", "<CLIENT_SECRET>"};
    const std::string payload = R"({
        "jsonrpc": "2.0",
        "method": "private/buy",
        "params": {"instrument_name": "ETH-PERPETUAL", "type": "limit", "price": 3500.5, "amount": 10},
        "id": 2
    })";
    auto [status, body] = api.api_private(payload);
}
```

## 3) Using `User` helpers
```cpp
#include "User.hpp"

int main() {
    User user;
    auto [s1, r1] = user.get_orderbook("ETH-PERPETUAL", 10);
    auto [s2, r2] = user.view_position("ETH-PERPETUAL");
}
```