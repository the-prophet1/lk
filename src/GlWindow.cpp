#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GlWindow.h"

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

        clearColor();

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
    backgroud = {
            .R =  red,
            .G = green,
            .B = blue,
            .A = alpha,
    };
}


void GlWindow::TestDo(unsigned int shaderProgram, unsigned int VAO, unsigned int VAO2) {
    while (!glfwWindowShouldClose(glWindow)) {

        clearColor();
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);



        // check event
        glfwSwapBuffers(glWindow);
        glfwPollEvents();
    }
}

void GlWindow::clearColor() {
    glClearColor(backgroud.R, backgroud.G, backgroud.B, backgroud.A);
    glClear(GL_COLOR_BUFFER_BIT);
}
