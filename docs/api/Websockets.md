# WebSockets

Transport layer is abstracted by `Socket` with two implementations.

## Socket (abstract)
```cpp
class Socket {
public:
    virtual ~Socket();
    virtual void switch_to_ws() = 0;
    [[nodiscard]] virtual std::pair<int, std::string> ws_request(const std::string& msg) = 0;
protected:
    const std::string host = "test.deribit.com";
    const std::string port = "443";
};
```

- **switch_to_ws()**: Establishes a secure WebSocket connection to the configured host/port.
- **ws_request(msg)**: Sends a JSON-RPC payload string and returns `{status, body}`.

## BSocket (Boost.Beast)
```cpp
class BSocket : public Socket {
public:
    BSocket();
    ~BSocket();
    void switch_to_ws() override;
    [[nodiscard]] std::pair<int, std::string> ws_request(const std::string& msg) override;
};
```
- Uses Boost.Beast with OpenSSL for TLS.

## Socketpp (websocketpp)
```cpp
class Socketpp : public Socket {
public:
    Socketpp();
    ~Socketpp();
    void switch_to_ws() override;
    [[nodiscard]] std::pair<int, std::string> ws_request(const std::string& msg) override;
};
```
- Uses websocketpp with Asio TLS.

## Selecting the Implementation
On `Api` construction, you are prompted to select:
- `1` → `BSocket`
- `2` → `Socketpp`
- Other → defaults to `Socketpp`