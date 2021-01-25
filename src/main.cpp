#include <iostream>
#include "GlWindow.h"
#include "VAO.h"
#include "shader/Shader.h"
#include "shader/VertexShader.h"
#include "shader/FragmentShader.h"
#include "shader/ShaderProgram.h"

float vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f
};


float vertices2[] = {
        0.0f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f
};


float vertices3[] = {
        -0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.0f,
};

int indices[] = { // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
};

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "\n"
                                 "void main(){\n"
                                 "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

int main() {
    GlWindow glWindow = GlWindow(3, 3);
    if (glWindow.CreateWindow(800, 600, "my window") != nullptr) {
        return 0;
    }

    glWindow.SetClearColor(1.0f, 1.0f, 0.5f, 1.0f);

    //create vertex shader and compile source
    Shader* vertexShader = new VertexShader(R"(D:\source\C++\lk\vert\triangle.shader)");
    auto err = vertexShader->LoadSource().Compile().Error();
    if (err != nullptr){
        std::cout << err << std::endl;
    }

    //create fragment shader and compile source
    Shader* fragmentShader = new FragmentShader(R"(D:\source\C++\lk\frag\triangle.shader)");
    err = fragmentShader->LoadSource().Compile().Error();
    if (err != nullptr){
        std::cout << err << std::endl;
    }

    ShaderProgram shaderProgram;
    shaderProgram.Link({vertexShader,fragmentShader});

    //delete shader
    delete vertexShader;
    delete fragmentShader;

    VAO vao1;
    vao1.SetVBOValue(Matrix<float>(vertices, 3, 3));

    VAO vao2;
    vao2.SetVBOValue(Matrix<float>(vertices2, 3, 3));

    VAO vao3;
    vao3.SetVBOValue(Matrix<float>(vertices3, 4, 3));
    vao3.SetVEOValue(Matrix<int>(indices, 2, 3));

    glWindow.TestDo(shaderProgram, vao1, vao3);

    return 0;
}
