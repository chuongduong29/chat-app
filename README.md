# 🚀 Chat App (C++17 + Boost.Asio + Protobuf)

A simple multi-client chat application built with modern C++ using asynchronous networking, Protocol Buffers for serialization, and Docker for deployment.

---

# 🧱 Tech Stack

* C++17
* Boost.Asio (async TCP networking)
* Protobuf (message serialization)
* CMake (build system)
* Google Test (unit testing)
* Docker & Docker Compose

---

# 📦 Features

* Multi-client chat server
* Asynchronous I/O (non-blocking)
* TCP framing (length-prefix)
* Protobuf-based protocol
* Thread-safe session management
* Graceful disconnect handling

---

# 🐳 1. Build (Docker)

Build server image:

```bash
docker build -f Dockerfile.server -t chat-server .
```

Build client image:

```bash
docker build -f Dockerfile.client -t chat-client .
```

---

# ▶️ 2. Run

## ✅ Option 1: Using docker-compose (Recommended)

```bash
docker-compose up --build
```

This will:

* Start server
* Start multiple clients

---

## ✅ Option 2: Manual run

### Run server

```bash
./server
```

### Run client

```bash
./client
```

---

# 💬 Usage

1. Start server
2. Open multiple clients
3. Enter username
4. Start chatting 🎉

---

# 🧪 3. Test

## Run unit tests

```bash
cd build
ctest
```

## What is tested?

* TCP framing (pack/unpack)
* Partial message handling
* Multiple message parsing
* Protobuf serialization/deserialization

---

# 🧠 Design Overview

## 📡 Protocol

* Protobuf message:

  * JOIN
  * MESSAGE
  * LEAVE

---

## 🔌 TCP Framing

TCP is stream-based → implemented:

```
[length (4 bytes)][data]
```

Ensures:

* correct message boundaries
* handles partial & multiple messages

---

## ⚙️ Concurrency Model

* Boost.Asio async model
* One `Session` per client
* `SessionManager` manages all clients
* Write queue prevents concurrent write issues

---

# 📁 Project Structure

```
chat-app/
├── proto/
├── src/
│   ├── server/
│   ├── client/
│   └── common/
├── tests/
├── Dockerfile.server
├── Dockerfile.client
└── docker-compose.yml
```

---

# ⚠️ Notes

* Handles multiple clients concurrently
* Safe disconnect (no crash)
* Handles malformed / partial TCP data
* Designed with production mindset

---

# 🎯 Future Improvements

* Authentication (unique username)
* Private messaging
* GUI client
* Epoll-based optimization
* TLS encryption

---
