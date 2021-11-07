cmake_minimum_required(VERSION 3.0.0)

project(Replayer)
# glog
FIND_PACKAGE(Glog REQUIRED)
include_directories(BEFORE ${GLOG_INCLUDE_DIRS})

include_directories(./)

add_executable(${PROJECT_NAME} main.cpp)


target_link_libraries(${PROJECT_NAME} -pthread glog::glog)