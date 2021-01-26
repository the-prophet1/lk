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
        lib/glad.c
        src/GlWindow.cpp
        src/GlWindow.h
        src/object/Resource.cpp
        src/object/Resource.h
        src/tool/Matrix.hpp
        src/shader/VertexShader.cpp
        src/shader/VertexShader.h
        src/shader/FragmentShader.cpp
        src/shader/FragmentShader.h
        src/shader/Shader.cpp
        src/shader/Shader.h
        src/shader/ShaderProgram.cpp
        src/shader/ShaderProgram.h lib/include/stb_image.h src/texture/Texture.cpp src/texture/Texture.h)

target_link_libraries(lk glfw3 pthread)