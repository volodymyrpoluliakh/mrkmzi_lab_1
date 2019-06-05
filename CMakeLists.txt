cmake_minimum_required(VERSION 2.8)

project(bigint)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

add_executable(${PROJECT_NAME} main.cpp big_int.cpp)


target_link_libraries(${PROJECT_NAME} PRIVATE gmp.a)
#target_link_libraries(${PROJECT_NAME} PRIVATE gmp.a libstdc++.a)
