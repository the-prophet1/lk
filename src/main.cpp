#include <iostream>
#include "GlWindow.h"
#include "shader/Shader.h"
#include "shader/VertexShader.h"
#include "shader/FragmentShader.h"
#include "shader/ShaderProgram.h"

float vertices[] = {
        -0.5f, 0.5f, 0.0f,       //左上角
        0.5f, 0.5f, 0.0f,      //右上角
        0.5f, -0.5f, 0.0f,     //右下角
        -0.5f, -0.5f, 0.0f,        //左下角
};

float color[] = {
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
};

float texCoords[] = {
        0.0f, 1.0f, // 左上角
        1.0f, 1.0f, // 右上角
        1.0f, 0.0f, //右下角
        0.0f, 0.0f // 左下角
};

int indices[] = { // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
};


int main() {
    GlWindow glWindow = GlWindow(3, 3);
    if (glWindow.CreateWindow(800, 600, "my window") != nullptr) {
        return 0;
    }
    glWindow.SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    //create vertex shader and compile source
    Shader *vertexShader = new VertexShader(R"(D:\source\C++\lk\vert\triangle.shader)");
    if (vertexShader->LoadSource().Compile().Error() != nullptr) {
        std::cout << vertexShader->Error() << std::endl;
    }

    //create fragment shader and compile source
    Shader *fragmentShader = new FragmentShader(R"(D:\source\C++\lk\frag\triangle.shader)");
    if (fragmentShader->LoadSource().Compile().Error() != nullptr) {
        std::cout << fragmentShader->Error() << std::endl;
    }

    ShaderProgram shaderProgram;
    if (shaderProgram.Link({vertexShader, fragmentShader}).Error() != nullptr) {
        std::cout << shaderProgram.Error() << std::endl;
    }

    //delete shader
    delete vertexShader;
    delete fragmentShader;

    Resource vao1;
    if (vao1.PushVBOValue(Matrix<float>(vertices, 4, 3))
                .PushVBOValue(Matrix<float>(color, 4, 3))
                .PushVBOValue(Matrix<float>(texCoords, 4, 2)).
                    SetEBOValue(Matrix<int>(indices, 2, 3)).
                    SetTexture(R"(D:\arith.jpg)").Error() != nullptr) {
        std::cout << vao1.Error() << std::endl;
    }

    vao1.Apply();
    glWindow.TestDo(shaderProgram, vao1);

    return 0;
}
