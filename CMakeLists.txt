cmake_minimum_required(VERSION 3.10)
project(ChatApp)

set(CMAKE_CXX_STANDARD 17)

# Find protobuf
find_package(Protobuf REQUIRED)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system)

# Include protobuf headers
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Boost_INCLUDE_DIRS})

# Proto file
set(PROTO_FILE proto/chat.proto)

# Generate protobuf sources
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILE})

# ===== Server =====
add_executable(server
    src/server/main.cpp
    src/server/chat_server.cpp
    src/server/session.cpp
    src/server/session_manager.cpp
    src/common/message_framer.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

target_link_libraries(server
    ${Protobuf_LIBRARIES}
    ${Boost_LIBRARIES}
)

# ===== Client =====
add_executable(client
    src/client/main.cpp
    src/client/client.cpp
    src/common/message_framer.cpp
    ${PROTO_SRCS}
)

target_link_libraries(client
    ${Boost_LIBRARIES}
    ${Protobuf_LIBRARIES}
)

add_executable(test_framer
    tests/test_framer.cpp
    src/common/message_framer.cpp
)
