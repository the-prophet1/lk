#ifndef LK_SHADERPROGRAM_H
#define LK_SHADERPROGRAM_H


#include "Shader.h"
#include "../object/Resource.h"
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef std::string string;

class ShaderProgram;

typedef void (*func)(ShaderProgram& shaderProgram);

class ShaderProgram {
public:
    ShaderProgram();

    ~ShaderProgram();

    ShaderProgram &Link(std::initializer_list<Shader *> il);

    ShaderProgram &SetUniform(const string &name, float v1, float v2, float v3, float v4);

    ShaderProgram &SetUniform(const string &name, int v1, int v2, int v3, int v4);

    ShaderProgram &SetUniform(const string &name, int v1);

    ShaderProgram &SetUniform(const string &name,glm::mat4& mat4);

    ShaderProgram &RegisterUniform(func handle);

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
    std::vector<func> handles;
};


#endif //LK_SHADERPROGRAM_H
