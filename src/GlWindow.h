#ifndef LK_GLWINDOW_H
#define LK_GLWINDOW_H

#include <string>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "object/Resource.h"
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

    void TestDo(ShaderProgram& shaderProgram, const Resource& VAO1);

    void SetClearColor(float red, float green, float blue, float alpha);

    ~GlWindow();

    GLFWwindow *GetGlWindow();

    void ClearColor();

private:
    void initErrorMap();

    static void resizeWindow(GLFWwindow *window, int width, int height);

private:
    GLFWwindow *glWindow{};
    std::map<int, const char *> errMap;
    RGBA background{};
};


#define CREATE_WINDOW_ERR 1
#define INIT_GLAD_ERR 2

#endif