cmake_minimum_required (VERSION 3.0.0)

set(CMAKE_CXX_FLAGS "-std=c++1z -O2")

include_directories(../include)

project (course)
add_executable(	course
                main.cpp
                parse.cpp
                search_server.cpp)
