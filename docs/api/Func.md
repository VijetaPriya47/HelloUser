# Func declarations

The `Func.hpp` header declares high-level trading operations (implemented as `User` methods).

## Header
```cpp
#include "Func.hpp"
```

## Declarations
```cpp
std::pair<int, std::string> place_order(const std::string &, double, int);
std::pair<int, std::string> cancel_order(const std::string &);
std::pair<int, std::string> modify_order(const std::string &, double, int);
std::pair<int, std::string> get_orderbook(const std::string &, int);
std::pair<int, std::string> view_position(const std::string &);
std::pair<int, std::string> get_openorders(const std::string &);
std::pair<int, std::string> get_marketdata(const std::string &, int);
```

These functions are bound to member implementations in `User`:
- `User::place_order`, `User::cancel_order`, `User::modify_order`, etc.

Prefer using the `User` methods directly.