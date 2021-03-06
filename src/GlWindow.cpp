#include <cmath>
#include <ctime>
#include <iostream>
#include <pthread_time.h>
#include "GlWindow.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


GlWindow::GlWindow(int glVersionMajor, int glVersionMinor, int glProfile) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, glProfile);
}

const char *GlWindow::CreateWindow(int width, int height, const char *title) {
    glWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (glWindow == nullptr) {
        return errMap[CREATE_WINDOW_ERR];
    }
    glfwMakeContextCurrent(glWindow);
    glfwSetFramebufferSizeCallback(glWindow, resizeWindow);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        return errMap[INIT_GLAD_ERR];
    }

    return nullptr;
}


void GlWindow::initErrorMap() {
    errMap[CREATE_WINDOW_ERR] = "create window error";
    errMap[INIT_GLAD_ERR] = "failed to initialize GLAD";
}

GlWindow::~GlWindow() {
    glfwTerminate();
}

void GlWindow::resizeWindow(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void GlWindow::Do() {
    while (!glfwWindowShouldClose(glWindow)) {

        ClearColor();

        // check event
        glfwSwapBuffers(glWindow);
        glfwPollEvents();
    }
}

void GlWindow::InputKeyboard(int key) {
    if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glWindow, true);
}

void GlWindow::SetClearColor(float red, float green, float blue, float alpha) {
    background = {
            .R =  red,
            .G = green,
            .B = blue,
            .A = alpha,
    };
}


void GlWindow::TestDo(ShaderProgram &shaderProgram, const Resource &vao) {
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(glWindow)) {
        ClearColor();
        if (shaderProgram.DrawTriangle(vao).Error() != nullptr) {
            std::cout << shaderProgram.Error() << std::endl;
        }

        // check event
        glfwSwapBuffers(glWindow);
        glfwPollEvents();
    }
}

void GlWindow::ClearColor() {

    glClearColor(background.R, background.G, background.B, background.A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLFWwindow *GlWindow::GetGlWindow() {
    return glWindow;
}
