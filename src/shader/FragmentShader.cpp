#include <glad/glad.h>
#include "FragmentShader.h"

FragmentShader::FragmentShader(std::string file) : Shader(std::move(file)) {
    shaderID = glCreateShader(GL_FRAGMENT_SHADER);
}

const char *FragmentShader::Error() {
    if (error != nullptr) {
        return std::string("FragmentShader error:").append(error).c_str();
    } else {
        return nullptr;
    }
}