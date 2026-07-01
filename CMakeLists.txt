cmake_minimum_required(VERSION 3.15)
project(FourFish VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

add_executable(FourFish 
    src/main.cpp
    src/BitBoard.cpp
    src/Engine.cpp
    src/TUI.cpp
)

target_include_directories(FourFish PRIVATE include)
