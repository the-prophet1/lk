#ifndef LK_GLWINDOW_H
#define LK_GLWINDOW_H

#include <string>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VAO.h"
#include "shader/ShaderProgram.h"

struct RGBA {
    float R;
    float G;
    float B;
    float A;
};

class GlWindow {
public:
    GlWindow(int VersionMajor, int VersionMinor, int glProfile = GLFW_OPENGL_CORE_PROFILE);

    const char *CreateWindow(int width, int height, const char *title);

    void InputKeyboard(int key);

    void Do();

    void TestDo(ShaderProgram& shaderProgram, VAO VAO1, VAO VAO2);

    void SetClearColor(float red, float green, float blue, float alpha);

    ~GlWindow();

private:
    void initErrorMap();

    void clearColor();

    static void resizeWindow(GLFWwindow *window, int width, int height);

private:
    GLFWwindow *glWindow;
    std::map<int, const char *> errMap;
    RGBA backgroud;
};


#define CREATE_WINDOW_ERR 1
#define INIT_GLAD_ERR 2

#endif