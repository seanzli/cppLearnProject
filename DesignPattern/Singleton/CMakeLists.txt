cmake_minimum_required(VERSION 3.0.0)

project(SingletonTest)

add_executable(${PROJECT_NAME} singleton.cpp)

target_link_libraries(${PROJECT_NAME} -pthread)