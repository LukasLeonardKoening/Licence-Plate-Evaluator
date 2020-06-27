cmake_minimum_required(VERSION 3.7)

project(LicencePlateRecognizer)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

file(GLOB executables src/*.cpp)

add_executable(LicencePlateRecognizer ${executables})
