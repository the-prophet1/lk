#include <glad/glad.h>
#include <cstdarg>
#include <iostream>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
    programID = glCreateProgram();
}


ShaderProgram &ShaderProgram::Link(std::initializer_list<Shader *> il) {
    if (error != nullptr) {
        return *this;
    }
    for (const auto &ptr : il) {
        glAttachShader(programID, ptr->GetID());
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
        return error;
    } else {
        return nullptr;
    }
}


ShaderProgram &ShaderProgram::SetUniform(const std::string &name, float v1, float v2, float v3, float v4) {
    if (error != nullptr) {
        return *this;
    }
    int location = findUniform(name);
    if (location == -1) {
        return *this;
    }
    glUniform4f(location, v1, v2, v3, v4);
    return *this;
}

ShaderProgram &ShaderProgram::SetUniform(const std::string &name, int v1, int v2, int v3, int v4) {
    if (error != nullptr) {
        return *this;
    }
    int location = findUniform(name);
    if (location == -1) {
        return *this;
    }
    glUniform4i(location, v1, v2, v3, v4);
    return *this;
}

int ShaderProgram::findUniform(const std::string &name) {
    int location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        error = "Not find uniform location";
    }
    glUseProgram(programID);
    return location;
}

ShaderProgram &ShaderProgram::PushVAO(const VAO &vao) {
    if (error != nullptr) {
        return *this;
    }
    vaos.push_back(vao);
    return *this;
}

ShaderProgram &ShaderProgram::DrawTriangle(const VAO &vao) {

    glUseProgram(programID);
    glBindVertexArray(vao.GetVaoId());
    glDrawArrays(GL_TRIANGLES, 0, 3);
    return *this;
}
