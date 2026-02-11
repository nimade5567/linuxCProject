cmake_minimum_required(VERSION 3.28)

project(Server)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(Server main.cpp
                src/threadPool.cpp
)
