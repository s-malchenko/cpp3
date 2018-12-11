cmake_minimum_required (VERSION 3.0.0)

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "-std=c++1z -O2")

include_directories(./)

project (course)
add_executable(	course
                server_stats.cpp
                stats.cpp)
