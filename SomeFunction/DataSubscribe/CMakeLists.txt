cmake_minimum_required(VERSION 3.0.0)
project(DataSubstribe VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

include_directories(../include)

# glog
find_package(glog 0.5.0 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} -lglog -lgflags -lpthread)