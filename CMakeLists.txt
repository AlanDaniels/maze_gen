cmake_minimum_required(VERSION 3.0)

project(mazegen LANGUAGES C)

add_executable(mazegen main.c)

install(TARGETS mazegen RUNTIME DESTINATION bin)
