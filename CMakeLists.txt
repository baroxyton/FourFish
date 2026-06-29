cmake_minimum_required(VERSION 3.15)
project(FourFish VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(FourFish 
    src/main.cpp
    src/BitBoard.cpp
    src/Engine.cpp
)

target_include_directories(FourFish PRIVATE include)
