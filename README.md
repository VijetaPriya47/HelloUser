# 🚀 **Project: Low Latency Trading System**

This project is a C++-based trading system that uses WebSockets for real-time data distribution and integrates several third-party libraries for logging, JSON parsing, and secure communication.

---

## 🛠️ **Dependencies**

To build and run this project, you need the following dependencies:

### 📦 **System Requirements**
- **C++ Compiler:** `g++` or `clang++` (supporting C++17 or higher)
- **Build System:** `meson` and `ninja`
- **Linux Tools:** `make`, `pkg-config`

### 🔥 **Required Libraries**
Ensure the following libraries are installed:
```bash
# Install Boost for system utilities
sudo apt install libboost-dev libboost-system-dev

# Install OpenSSL for secure communication
sudo apt install libssl-dev

# Install Spdlog for logging
sudo apt install libspdlog-dev

# Install nlohmann_json for JSON parsing
sudo apt install nlohmann-json3-dev
```
---

# ⚙️ **Build Instructions**

Follow these steps to build and run the project:

---

## ✅ **1. Clone the Repository**
First, clone the repository to your local machine:
```bash
git clone <repository_url>
cd <project_directory>
```

## 🔧 **2. Install Dependencies**
Ensure the required dependencies are installed. Use the following commands to install them:

###📦 **System Tools**
```bash
sudo apt install meson ninja-build
```
###🔥 **Libraries**

```bash
# Boost for system utilities
sudo apt install libboost-dev libboost-system-dev

# OpenSSL for secure communication
sudo apt install libssl-dev

# Spdlog for logging
sudo apt install libspdlog-dev

# nlohmann_json for JSON parsing
sudo apt install nlohmann-json3-dev
```
###🛠️ 3. **Build the Project**

🛠️ Create the Build Directory
Run the following command to create the build directory:

```bash
meson setup build
```
###🚀 Compile the Project
Once the build setup is complete, compile the project:

```bash
meson compile -C build
```

🚀 4. Run the Executable
After a successful build, run the executable:

```bash
./build/main
```

###🔥 **Run with Debug Logs**
To enable debug-level logging:

```bash
SPDLOG_LEVEL=debug ./build/main
```
##🛠️ **Troubleshooting**

Missing Dependencies:
If you encounter missing dependencies, install them using:

```bash
sudo apt install <missing_library>
```

Rebuild the Project:
If you modify the source code, you can rebuild using:

```bash
meson compile -C build
```

# 🔍 **Project Structure**

The project is organized into the following files and directories:

```plaintext
📁 src/                     # Source files
 ├── main.cpp               # Entry point of the application
 ├── User.cpp               # Handles user actions and interactions
 ├── User.hpp               # Header file for the User class
 ├── Api.cpp                # API integration for trading functions
 ├── Api.hpp                # Header file for API class
 ├── Socket.cpp             # WebSocket handling for real-time data
 ├── Socket.hpp             # Header file for Socket class
 ├── Params.cpp             # Configuration parameters and constants
 ├── Params.hpp             # Header file for Params
 ├── Func.cpp               # Utility functions for common operations
 ├── Func.hpp               # Header file for Func utilities
 ├── boost.cpp              # Boost library integrations
 ├── boost.hpp              # Header file for Boost functions
 ├── zsocket.cpp            # Socket communication logic
 ├── zsocket.hpp            # Header file for zsocket class
 ├── Spdlog.cpp             # Logging functionality using Spdlog
 ├── Spdlog.hpp             # Header file for Spdlog configurations
 📄 meson.build              # Meson build configuration
 📄 README.md                # Project documentation
```

---

## 📚 Documentation
- Docs index: `docs/README.md`
- Overview: `docs/overview.md`
- API Reference: `docs/api/Api.md`, `docs/api/User.md`, `docs/api/Websockets.md`
- Guides: `docs/guides/usage.md`
- Examples: `docs/examples.md`
