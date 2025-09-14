# Params helpers

Helpers that orchestrate console input and invoke actions. Exposed in `Params.hpp`.

## Header
```cpp
#include "Params.hpp"
```

## Functions
```cpp
int process_cancel_order(const std::function<std::pair<int, std::string>(std::string)> &action);
int process_place_order(const std::function<std::pair<int, std::string>(std::string, double, int)> &action);
int process_modify_order(const std::function<std::pair<int, std::string>(std::string, double, int)> &action);
int process_order_book(const std::function<std::pair<int, std::string>(std::string, int)> &action);
int process_view_position(const std::function<std::pair<int, std::string>(std::string)> &action);
int process_open_orders(const std::function<std::pair<int, std::string>(std::string)> &action);
int process_market_data(const std::function<std::pair<int, std::string>(std::string, int)> &action);
```

- Each function collects user input, calls `action(...)`, and returns a combined status (bitwise OR with `display_response`).
- Used by `User::Start()` to implement interactive flows.

## Example
```cpp
User user;
int status = user.process_place_order([&](const std::string &inst, double price, int qty) {
    return user.place_order(inst, price, qty);
});
```