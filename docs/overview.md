# Overview

This project is a C++-based trading system using WebSockets for real-time communication with a crypto exchange API (Deribit-style JSON-RPC). It provides:

- An interactive console dashboard via the `User` class
- An `Api` class to send authenticated and public JSON-RPC requests over WebSockets
- Pluggable WebSocket transports via an abstract `Socket` interface with concrete implementations `BSocket` (Boost.Beast + OpenSSL) and `Socketpp` (websocketpp + Asio TLS)
- Integrated logging via `spdlog` with logs written to `logs/json_responses.log`

## Architecture
- `main.cpp` creates a `User` and runs the interactive dashboard.
- `User` orchestrates user flows (order placement, cancellation, market data, etc.). It constructs an `Api` instance, which in turn initializes a WebSocket `Socket` implementation and performs authentication.
- `Api` exposes `api_public` and `api_private` to send raw JSON-RPC payloads through the selected `Socket`.
- `Socket` is an abstract base defining `switch_to_ws()` and `ws_request(std::string)`.

## Key Paths
- Runtime logs: `logs/json_responses.log`
- Headers: `src/*.hpp`, `src/Websockets/*.hpp`
- Implementations: `src/*.cpp`, `src/Websockets/*.cpp`

## Building & Running
See the root `README.md` for Meson/Ninja build steps and requirements. After building, run `./build/main` and follow the interactive menus.

## Note on Interactivity
Both `User` and `Api` constructors prompt for input:
- `User` asks for authentication mode (guest or custom credentials).
- `Api` asks you to choose socket implementation (Boost or ZSocket/websocketpp) and immediately attempts authentication.

If you require fully programmatic usage without console prompts, you may adapt constructors to accept configuration parameters instead of reading from `std::cin`.