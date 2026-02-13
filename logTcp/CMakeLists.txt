cmake_minimum_required(VERSION 3.28)

project(logTcp)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(logTcp main.cpp
                src/log.cpp
                src/tcpServer.cpp
)