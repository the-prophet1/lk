#ifndef LK_SHADER_H
#define LK_SHADER_H

#include <string>

#define CompileInfoSize 512

class Shader {
public:
    explicit Shader(std::string file);

    virtual Shader &Compile();

    virtual Shader &LoadSource();

    virtual const char *Error() = 0;

    virtual unsigned int GetID();

    virtual ~Shader();

protected:
    virtual void checkCompile();

protected:
    std::string file;
    std::string source;
    unsigned int shaderID{};
    const char *error{};
    char compileError[CompileInfoSize]{};
};

#endif //LK_SHADER_H
