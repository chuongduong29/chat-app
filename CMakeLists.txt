cmake_minimum_required(VERSION 3.10)
project(ChatApp)

set(CMAKE_CXX_STANDARD 17)

# Find protobuf
find_package(Protobuf REQUIRED)

# Include protobuf headers
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Proto file
set(PROTO_FILE proto/chat.proto)

# Generate protobuf sources
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILE})

# ===== Server =====
add_executable(server
    src/server/main.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

target_link_libraries(server
    ${Protobuf_LIBRARIES}
)

# ===== Client =====
add_executable(client
    src/client/main.cpp
    ${PROTO_SRCS}
)

target_link_libraries(client
    ${Protobuf_LIBRARIES}
)
