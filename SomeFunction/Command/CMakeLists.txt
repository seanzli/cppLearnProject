cmake_minimum_required(VERSION 3.0.0)

project(CommandTest)

set(CMAKE_CXX_STANDARD 14)

include_directories(./)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} -pthread)