cmake_minimum_required(VERSION 3.0.0)

project(GpsTimeTest)
set(CMAKE_CXX_STANDARD 14)

include_directories(./include)

add_executable(${PROJECT_NAME} main.cpp)