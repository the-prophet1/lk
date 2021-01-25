#include <glad/glad.h>
#include <cstdarg>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
    programID = glCreateProgram();
}


ShaderProgram &ShaderProgram::Link(std::initializer_list<Shader*> il) {
    if (error != nullptr) {
        return *this;
    }
    for (const auto & ptr : il) {
        glAttachShader(programID,ptr->GetID());
    }
    glLinkProgram(programID);
    checkLink();
    return *this;
}

void ShaderProgram::checkLink() {
    int success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, nullptr, linkError);
        error = linkError;
    }
}

const char *ShaderProgram::Error() {
    if (error != nullptr) {
        return std::string("ShaderProgram error:").append(error).c_str();
    } else {
        return nullptr;
    }
}

void ShaderProgram::Use() {
    glUseProgram(programID);
}
