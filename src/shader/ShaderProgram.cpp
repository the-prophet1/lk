#include <glad/glad.h>
#include <cstdarg>
#include <iostream>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
    programID = glCreateProgram();
}


ShaderProgram &ShaderProgram::Link(std::initializer_list<Shader *> il) {
    if (!error.empty()) {
        return *this;
    }
    for (const auto &ptr : il) {
        glAttachShader(programID, ptr->GetShaderID());
    }
    glLinkProgram(programID);
    checkLink();
    return *this;
}

void ShaderProgram::checkLink() {
    if (!error.empty()) {
        return;
    }
    int success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, nullptr, linkError);
        error = linkError;
    }
}

const char *ShaderProgram::Error() {
    if (!error.empty()) {
        return error.c_str();
    } else {
        return nullptr;
    }
}


ShaderProgram &ShaderProgram::SetUniform(const std::string &name, float v1, float v2, float v3, float v4) {
    if (!error.empty()) {
        return *this;
    }
    int location = findUniform(name);
    if (!error.empty()) {
        return *this;
    }
    glUniform4f(location, v1, v2, v3, v4);
    return *this;
}

ShaderProgram &ShaderProgram::SetUniform(const std::string &name, int v1, int v2, int v3, int v4) {
    if (!error.empty()) {
        return *this;
    }
    int location = findUniform(name);
    if (!error.empty()) {
        return *this;
    }
    glUniform4i(location, v1, v2, v3, v4);
    return *this;
}

ShaderProgram &ShaderProgram::SetUniform(const string &name, int v1) {
    if (!error.empty()) {
        return *this;
    }
    int location = findUniform(name);
    if (!error.empty()) {
        return *this;
    }
    glUniform1i(location, v1);
    return *this;
}

int ShaderProgram::findUniform(const std::string &name) {
    if (!error.empty()) {
        return -1;
    }
    int location = glGetUniformLocation(programID, name.c_str());
    if (location == -1) {
        error.append("Not find uniform location: ").append(name);
    }
    glUseProgram(programID);
    return location;
}


ShaderProgram &ShaderProgram::DrawTriangle(const Resource &resource) {
    if (!error.empty()) {
        return *this;
    }
    glUseProgram(programID);

    if (resource.GetVaoID() != 0) {
        glBindVertexArray(resource.GetVaoID());
    }

    for (int i = 0; i < resource.GetTextureIDs().size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, resource.GetTextureIDs()[i]);
    }

    glDrawArrays(GL_TRIANGLES, 0, 3);
    return *this;
}

ShaderProgram &ShaderProgram::DrawElements(const Resource &resource) {
    if (!error.empty()) {
        return *this;
    }
    glUseProgram(programID);

    if (resource.GetVaoID() != 0) {
        glBindVertexArray(resource.GetVaoID());
    }
    for (int i = 0; i < resource.GetTextureIDs().size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, resource.GetTextureIDs()[i]);
    }

    glDrawElements(GL_TRIANGLES, resource.GetIndices().Row() * resource.GetIndices().Column(), GL_UNSIGNED_INT,
                   nullptr);
    return *this;
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programID);
}


