#include <iostream>
#include "GlWindow.h"
#include "object/VAO.h"
#include "shader/Shader.h"
#include "shader/VertexShader.h"
#include "shader/FragmentShader.h"
#include "shader/ShaderProgram.h"

float vertices[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
};

float color[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
};

float texCoords[] = {
        0.0f, 0.0f, // 左下角
        1.0f, 0.0f, // 右下角
        0.5f, 1.0f // 上中
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
    glWindow.SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    //create vertex shader and compile source
    Shader *vertexShader = new VertexShader(R"(D:1\source\C++\lk\vert\triangle.shader)");
    if (vertexShader->LoadSource().Compile().Error() != nullptr) {
        std::cout << vertexShader->Error() << std::endl;
    }

    //create fragment shader and compile source
    Shader *fragmentShader = new FragmentShader(R"(D:\source\C++\lk\frag\triangle.shader)");
    if (fragmentShader->LoadSource().Compile().Error() != nullptr) {
        std::cout << vertexShader->Error() << std::endl;
    }

    ShaderProgram shaderProgram;
    if (shaderProgram.Link({vertexShader, fragmentShader}).Error() != nullptr) {
        std::cout << shaderProgram.Error() << std::endl;
    }

    //delete shader
    delete vertexShader;
    delete fragmentShader;

    VAO vao1;
    vao1.PushVBOValue(Matrix<float>(vertices, 3, 3));
    vao1.PushVBOValue(Matrix<float>(color, 3, 3));
    vao1.SetVBOValue();

    shaderProgram.PushVAO(vao1);

    glWindow.TestDo(shaderProgram,vao1);

    return 0;
}
