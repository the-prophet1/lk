#include <iostream>
#include "GlWindow.h"
#include "VAO.h"

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

    glWindow.SetClearColor(0.5f, 1.0f, 0.5f, 1.0f);



    //create vertex shader and compile source
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    //check compile
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //create fragment shader and compile source
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    //check compile
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //create shader attach program and link
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check link
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::LINK_FAILED\n" << infoLog << std::endl;
    }
    //delete shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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
