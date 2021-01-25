#ifndef LK_SHADERPROGRAM_H
#define LK_SHADERPROGRAM_H


#include "Shader.h"

class ShaderProgram {
public:
    ShaderProgram();

    ShaderProgram &Link(std::initializer_list<Shader*> il);

    const char *Error();

    void Use();

private:
    void checkLink();

private:
    unsigned int programID;
    const char *error{};
    char linkError[CompileInfoSize]{};
};


#endif //LK_SHADERPROGRAM_H
