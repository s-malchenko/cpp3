cmake_minimum_required (VERSION 3.0.0)

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "-std=c++11 -std=gnu++17")

include_directories(../cpp2/test_runner)

project (course)
add_executable(	course
                max_element_if.cpp)
