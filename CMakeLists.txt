
cmake_minimum_required(VERSION 3.0.0)
project(bibparser)



add_executable(bibparser src/main.cpp)



set(CMAKE_CXX_STANDARD 14)
message("CXX Standard: ${CMAKE_CXX_STANDARD}")

