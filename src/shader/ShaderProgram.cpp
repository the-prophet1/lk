#include <glad/glad.h>
#include <cstdarg>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
    programID = glCreateProgram();
}


ShaderProgram &ShaderProgram::Link(int count, ...) {
    if (error != nullptr) {
        return *this;
    }

    va_list ap;  //声明一个va_list变量
    va_start(ap, count);
    for (int i = 0; i < count; i++) {
        
    }

    va_end(ap);  //用于清理


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
    return error;
}