cmake_minimum_required(VERSION 3.6)
project(dive)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.58.0 COMPONENTS program_options system log REQUIRED)

set(SOURCE_FILES main.cpp src/dive.cpp)
set(CMAKE_CXX_FLAGS "-pthread")

if (Boost_FOUND)
    add_definitions(-DBOOST_LOG_DYN_LINK)
    include_directories(${Boost_INCLUDE_DIRS})

    add_executable(dive ${SOURCE_FILES})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif ()
