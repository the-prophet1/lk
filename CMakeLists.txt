cmake_minimum_required(VERSION 3.10)
project(lk)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        "lib/include"
)

link_directories(
        "./lib"
)

add_executable(lk
        main.cpp
        src/glad.c
        )

target_link_libraries(lk glfw3)