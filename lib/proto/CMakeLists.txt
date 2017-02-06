cmake_minimum_required(VERSION 3.6)
project(dive_protobuf)

find_package(Protobuf REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Protobuf_INCLUDE_DIRS})
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER message.proto)
add_library(${PROJECT_NAME} ${PROTO_HEADER} ${PROTO_SRC})
target_link_libraries(${PROJECT_NAME} ${PROTOBUF_LIBRARIES})