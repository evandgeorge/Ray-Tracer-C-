cmake_minimum_required(VERSION 3.14)
project(RayTracerCPP)

include_directories(src)
add_subdirectory(test)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ray_Tracer main.cpp src/geometry/Vector3D.cpp src/geometry/Vector3D.h test/geometry/Vector3D_test.cpp src/geometry/Ray.cpp src/geometry/Ray.h test/geometry/Ray_test.cpp src/geometry/Shape.h src/geometry/Color.h test/geometry/Color_test.cpp src/geometry/Sphere.cpp src/geometry/Sphere.h test/geometry/Sphere_test.cpp)
target_link_libraries(Ray_Tracer gtest gtest_main)