#include <fstream>
#include <sstream>
#include "Shader.h"
#include "glad/glad.h"

Shader::Shader(std::string file) : file(std::move(file)) {

}

Shader &Shader::Compile() {
    if (!error.empty()) {
        return *this;
    }
    const char *s = source.c_str();
    glShaderSource(shaderID, 1, &s, nullptr);
    glCompileShader(shaderID);
    checkCompile();
    return *this;
}

Shader &Shader::LoadSource() {
    if (!error.empty()) {
        return *this;
    }
    std::ifstream ifStream(file);
    if (!ifStream.is_open()) {
        error.append("file doesn't exist: ").append(file);
        return *this;
    }
    std::stringstream buffer;
    buffer << ifStream.rdbuf();
    source = buffer.str();

    return *this;
}

void Shader::checkCompile() {
    int success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, CompileInfoSize, nullptr, compileError);
        error = compileError;
    }
}

Shader::~Shader() {
    if (shaderID != 0) {
        glDeleteShader(shaderID);
    }
}

unsigned int Shader::GetShaderID() const {
    return shaderID;
}


