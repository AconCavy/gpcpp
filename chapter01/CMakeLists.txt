cmake_minimum_required(VERSION 3.17)
project(c01)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 CONFIG REQUIRED)

add_executable(c01 main.cpp)
target_link_libraries(c01 PRIVATE SDL2::SDL2 SDL2::SDL2main)
