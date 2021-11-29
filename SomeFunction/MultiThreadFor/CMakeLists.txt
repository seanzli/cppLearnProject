cmake_minimum_required(VERSION 3.0.0)

project(MultiThreadFor)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("-std=c++14 -Wall -O3")

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} pthread)