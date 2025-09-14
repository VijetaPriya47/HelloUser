# Logging (Spdlog integration)

The project uses `spdlog` for structured logging. JSON responses are logged to `logs/json_responses.log`.

## Relevant Methods
```cpp
int User::display_response(const std::string &resp);
```
- Parses `resp` as JSON via `nlohmann::json`.
- Logs either `result` or the entire JSON.
- Logs errors if the `error` field exists or parsing fails.

## Initialization
The `User` constructor ensures a `logs` directory exists and configures a basic file sink:
- Logger name: `json_logger`
- File: `logs/json_responses.log`
- Pattern: `[%Y-%m-%d %H:%M:%S] %v`
- Flush on info

## Tips
- Set `SPDLOG_LEVEL=debug` when running to increase verbosity.
- You can replace the basic sink with rotating or asynchronous sinks as needed.