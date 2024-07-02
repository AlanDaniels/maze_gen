cmake_minimum_required(VERSION 3.5)

project(mazegen VERSION 1.0 LANGUAGES CXX)

file(GLOB sources *.cpp *.hpp)

add_executable(mazegen ${sources})

add_compile_options(mazgen PRIVATE -Wall -Wextra -Wpedantic)

set_target_properties(mazegen PROPERTIES
    CMAKE_CXX_STANDARD             17
    CMAKE_CXX_COMPILER             "/usr/bin/clang++"
    CMAKE_CXX_FLAGS                "-Wall -Wextra --verbose"
    CMAKE_CXX_FLAGS_DEBUG          "-g"
    CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG"
    CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG"
    CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g"
    CMAKE_INCLUDE_PATH "/usr/include/c++/11"
)

target_link_libraries(mazegen PUBLIC -lX11)

install(TARGETS mazegen RUNTIME DESTINATION bin)
