cmake_minimum_required(VERSION 3.6)
project(dive)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.58.0 COMPONENTS program_options system log date_time REQUIRED)

file(GLOB SOURCE_FILES "./src/*.cpp" "./include/*.h" "./lib/**/*.h")
set(CMAKE_CXX_FLAGS "-pthread")

add_subdirectory(lib/proto)

if (Boost_FOUND)
    add_definitions(-DBOOST_LOG_DYN_LINK)
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories(${CMAKE_CURRENT_BINARY_DIR})

    add_executable(dive main.cpp ${SOURCE_FILES})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} dive_protobuf ${PROTOBUF_LIBRARY})
endif ()

add_subdirectory(tests)