# 🚀 Chat App (C++17 + Boost.Asio + Protobuf)

A simple multi-client chat application built with modern C++ using asynchronous networking, Protocol Buffers for serialization, and Docker for deployment.

---

# 📖 Overview

This project demonstrates how to build a scalable, asynchronous TCP chat system in modern C++. It focuses on correctness, robustness, and production-style design, including proper message framing, concurrency handling, and fault tolerance.

The system supports multiple clients communicating through a central server using a structured protocol (Protobuf). It is designed to remain stable under stress, handle malformed data gracefully, and ensure reliable message broadcasting.

---

# 🎯 Objectives

* Build a real-time multi-client chat system
* Practice asynchronous networking with Boost.Asio
* Implement reliable TCP message framing
* Use Protocol Buffers for structured communication
* Ensure stability under stress and disconnect scenarios
* Follow clean architecture and thread-safe design principles

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

### ⚠️ "All commands run from project chat-app directory."

---

## ✅ Option 1: Using docker-compose (Recommended)

This is the easiest way to run the full system.

Command:
```bash
docker-compose up --build
```

What it does:
- Builds server image
- Builds client images
- Starts server container
- Starts multiple client containers
- Automatically creates internal network

---

## 🧪 Option 2: Manual run (Local development)

Use this if you want to debug or develop locally.

---

### 🔧 Step 1: Build project

```bash
mkdir -p build
cd build
cmake ..
make -j
```

---

### ▶️ Step 2: Run server

Open terminal 1:

```bash
cd build
./server
```

---

### ▶️ Step 3: Run client

Open terminal 2:

```bash
cd build
./client
```

You can run multiple clients by opening more terminals.

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

# 🧪 4. Integration Test (Manual)

## 🎯 Goal

Verify full system behavior:

* Multi-client communication
* Broadcast correctness
* Stability under disconnect / stress

---

## ✅ Test Case 1 — Basic Connection

**Steps**

1. Start server
2. Start 1 client

**Expected**

* Client connects successfully
* Server logs new connection

---

## ✅ Test Case 2 — Multiple Clients

**Steps**

1. Start server
2. Start 3 clients

**Expected**

* All clients connect
* No crash

---

## ✅ Test Case 3 — Basic Chat

**Steps**

1. Client A sends: `hello`

**Expected**

```
A: hello
```

* Other clients receive the message correctly

---

## ✅ Test Case 4 — Broadcast

**Steps**

1. Client A sends message

**Expected**

* All other clients receive the message

---

## ✅ Test Case 5 — Disconnect Handling

**Steps**

1. Start 3 clients
2. Kill 1 client (Ctrl+C)

**Expected**

* Server removes client
* No crash

---

## ✅ Test Case 6 — Stress Test (Spam)

**Steps**

1. Client A sends many messages quickly

**Expected**

* No crash
* Messages are still broadcast correctly

---

# 🧠 Design Overview

## 📡 Protocol

Protobuf message types:

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

* Correct message boundaries
* Handles partial & multiple messages

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