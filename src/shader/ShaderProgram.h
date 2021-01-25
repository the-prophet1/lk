#ifndef LK_SHADERPROGRAM_H
#define LK_SHADERPROGRAM_H


#include "Shader.h"
#include "../object/VAO.h"

class ShaderProgram {
public:
    ShaderProgram();

    ShaderProgram &Link(std::initializer_list<Shader *> il);


    ShaderProgram &SetUniform(const std::string &name, float v1, float v2, float v3, float v4);

    ShaderProgram &SetUniform(const std::string &name, int v1, int v2, int v3, int v4);

    ShaderProgram &PushVAO(const VAO& vao);

    ShaderProgram &DrawTriangle(const VAO& vao);

    const char *Error();


private:
    void checkLink();

    int findUniform(const std::string& name);

private:
    unsigned int programID;
    const char *error{};
    char linkError[CompileInfoSize]{};
    std::vector<VAO> vaos;
};


#endif //LK_SHADERPROGRAM_H
