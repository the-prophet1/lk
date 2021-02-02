#include <iostream>
#include "GlWindow.h"
#include "shader/Shader.h"
#include "shader/VertexShader.h"
#include "shader/FragmentShader.h"
#include "shader/ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] = {
        -0.5f, 0.5f, 0.0f,       //左上角
        0.5f, 0.5f, 0.0f,      //右上角
        0.5f, -0.5f, 0.0f,     //右下角
        -0.5f, -0.5f, 0.0f,        //左下角
};

float color[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
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


float verticesVBO[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f
};

float texCoordsVBO[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -9.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -7.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};

void cameraView(ShaderProgram &shaderProgram) {
// camera/view transformation
    glm::mat4 view; // make sure to initialize matrix to identity matrix first
    float radius = 30.0f;

    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    shaderProgram.SetUniform("view", view);
}

void cameraMove(ShaderProgram &shaderProgram) {
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    shaderProgram.SetUniform("view", view);
}


void transform(ShaderProgram &shaderProgram) {
    //   glm::mat4 trans;
    // 位移
    //  trans = glm::translate(trans, glm::vec3(0.75, 0.3, 0.0));
    // 缩放
//    trans = glm::scale(trans, glm::vec3(sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime())));
    // 旋转
//    trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0, 1.0, 1.0));
/*
    //使模型绕X轴旋转
    glm::mat4 model;
    model = glm::rotate(model, (float) glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    shaderProgram.SetUniform("model", model);
    // 使模型远离我们的摄像机
    glm::mat4 view;
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    shaderProgram.SetUniform("view", view);
    // 设置投影矩阵
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    shaderProgram.SetUniform("projection", projection);
 */

    // 使模型远离我们的摄像机
//    glm::mat4 view;
//    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//    shaderProgram.SetUniform("view", view);
    // 设置投影矩阵

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    shaderProgram.SetUniform("projection", projection);

    static int i = 0;
    if (i == 10) {
        i = 0;
    }
    glm::mat4 model;
    model = glm::translate(model, cubePositions[i++]);
    float angle = 20.0f * i;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    shaderProgram.SetUniform("model", model);
}


int main() {
    GlWindow glWindow = GlWindow(3, 3);
    if (glWindow.CreateWindow(800, 600, "my window") != nullptr) {
        return 0;
    }
    glWindow.SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
    if (vao1
                .PushVBOValue(Matrix<float>(verticesVBO, 36, 3))
//                .PushVBOValue(Matrix<float>(color, 4, 3))
                .PushVBOValue(Matrix<float>(texCoordsVBO, 36, 2))
//                .SetEBOValue(Matrix<int>(indices, 2, 3))
                .PushTexture(R"(D:\arith.jpg)")
//                .PushTexture(R"(D:\tifa.jpg)")
//                .PushTexture(R"(D:\container.jpg)")
                .Error() != nullptr) {
        std::cout << vao1.Error() << std::endl;
    }
    shaderProgram.SetUniform("ourTexture1", 0);

       shaderProgram.RegisterUniform(cameraView);
    for (int i = 0; i < 10; ++i) {
        shaderProgram.RegisterUniformDraw(transform);
    }


    vao1.Apply();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(glWindow.GetGlWindow())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (shaderProgram.DrawTriangle(vao1).Error() != nullptr) {
            std::cout << shaderProgram.Error() << std::endl;
        }

        // check event
        glfwSwapBuffers(glWindow.GetGlWindow());
        glfwPollEvents();
        //   glWindow.TestDo(shaderProgram, vao1);

    }
    return 0;
}

int main_bak() {
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 1.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;
    return 0;
};