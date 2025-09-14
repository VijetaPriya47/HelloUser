# Json

A lightweight struct used to hold JSON-RPC request fields.

## Header
```cpp
#include "Json.hpp"
```

## Definition
```cpp
struct Json {
    std::string method;
    std::string params;
    std::string id;
    const std::string jsonrpc = "2.0";
};
```

## Notes
- This struct is not directly serialized; it is a convenient holder. The rest of the code constructs JSON-RPC payloads as raw strings.
- You may prefer using `nlohmann::json` to build requests programmatically.

## Example (using nlohmann::json)
```cpp
#include <nlohmann/json.hpp>

nlohmann::json payload = {
    {"jsonrpc", "2.0"},
    {"id", 1},
    {"method", "public/get_order_book"},
    {"params", {{"instrument_name", "ETH-PERPETUAL"}, {"depth", 10}}}
};
std::string body = payload.dump();
```