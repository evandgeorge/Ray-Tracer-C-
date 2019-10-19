cmake_minimum_required(VERSION 3.14)
project(Ray_Tracer)

add_subdirectory(src)
add_subdirectory(test)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ray_Tracer main.cpp test/test.cpp)
target_link_libraries(Ray_Tracer gtest gtest_main)