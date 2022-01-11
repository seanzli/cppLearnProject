cmake_minimum_required(VERSION 3.0.0)

project(graphTest)

set(CMAKE_CXX_STANDARD 17)

include_directories(./)

add_executable(${PROJECT_NAME} main.cpp)