#include "VertexShader.h"

#include <utility>
#include <glad/glad.h>

VertexShader::VertexShader(std::string file) : Shader(std::move(file)) {
    shaderID = glCreateShader(GL_VERTEX_SHADER);
}

const char *VertexShader::Error() {
    return std::string("VertexShader error:").append(error).c_str();
}