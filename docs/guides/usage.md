# Usage Guide

This guide walks through building, running, and using the APIs.

## Build & Run
- Follow `README.md` to install dependencies.
- Build with Meson/Ninja:
```bash
meson setup build
meson compile -C build
./build/main
```

## Interactive Flow
1. Choose authentication mode:
   - `1` Guest (uses demo credentials)
   - `2` Custom (enter your client id/secret)
2. Choose socket implementation:
   - `1` Boost (BSocket)
   - `2` ZSocket (websocketpp)
3. Use the dashboard to place/cancel/modify orders, view book, positions, open orders, or market data subscriptions.

## Programmatic Examples

### Create Api and call public endpoint
```cpp
#include "Api.hpp"

int main() {
    Api api; // prompts for socket choice and authenticates
    const std::string payload = R"({
        "jsonrpc": "2.0",
        "id": 1,
        "method": "public/get_order_book",
        "params": {"instrument_name": "ETH-PERPETUAL", "depth": 10}
    })";
    auto [status, resp] = api.api_public(payload);
}
```

### Place an order via User convenience method
```cpp
#include "User.hpp"

int main() {
    User user; // prompts for auth mode and config
    auto [status, body] = user.place_order("ETH-PERPETUAL", 3500.5, 10);
}
```

## Logging
- Logs written to `logs/json_responses.log`.
- Set `SPDLOG_LEVEL=debug` to increase verbosity when running.