cmake_minimum_required(VERSION 3.6)
project(dive)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.63.0 REQUIRED system program_options)

set(SOURCE_FILES main.cpp)
add_executable(dive ${SOURCE_FILES})