#ifndef LK_FRAGMENTSHADER_H
#define LK_FRAGMENTSHADER_H


#include "Shader.h"

class FragmentShader : public Shader {
public:
    explicit FragmentShader(std::string file);

    const char* Error() override;

};


#endif //LK_FRAGMENTSHADER_H
