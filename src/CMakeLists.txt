cmake_minimum_required(VERSION 3.5)

project(mazegen VERSION 1.0 LANGUAGES CXX)
file(GLOB sources *.cpp *.hpp)
add_executable(mazegen ${sources})

target_compile_options(mazegen PRIVATE -std=c++17 -Wall -Wextra -g -Og)
target_link_libraries(mazegen PRIVATE -lX11)
