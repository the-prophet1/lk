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
        src/main.cpp
        src/glad.c
        src/GlWindow.cpp src/GlWindow.h src/VAO.cpp src/VAO.h src/Matrix.hpp src/shader/VertexShader.cpp src/shader/VertexShader.h src/shader/FragmentShader.cpp src/shader/FragmentShader.h src/shader/Shader.cpp src/shader/Shader.h src/shader/ShaderProgram.cpp src/shader/ShaderProgram.h)

target_link_libraries(lk glfw3)