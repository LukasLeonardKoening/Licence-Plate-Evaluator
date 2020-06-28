cmake_minimum_required(VERSION 3.7)

project(LicencePlateEvaluator)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

file(GLOB executables src/*.cpp src/licence_plate/*.cpp)

add_executable(LicencePlateEvaluator ${executables})
