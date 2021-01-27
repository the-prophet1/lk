#ifndef LK_SHADERPROGRAM_H
#define LK_SHADERPROGRAM_H


#include "Shader.h"
#include "../object/Resource.h"

typedef std::string string;

class ShaderProgram {
public:
    ShaderProgram();

    ~ShaderProgram();

    ShaderProgram &Link(std::initializer_list<Shader *> il);

    ShaderProgram &SetUniform(const string &name, float v1, float v2, float v3, float v4);

    ShaderProgram &SetUniform(const string &name, int v1, int v2, int v3, int v4);

    ShaderProgram &SetUniform(const string &name, int v1);

    ShaderProgram &DrawTriangle(const Resource& resource);

    ShaderProgram &DrawElements(const Resource& resource);

    const char *Error();


private:
    void checkLink();

    int findUniform(const std::string& name);

private:
    unsigned int programID;
    string error{};
    char linkError[CompileInfoSize]{};
};


#endif //LK_SHADERPROGRAM_H
