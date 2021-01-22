#ifndef LK_VERTEXSHADER_H
#define LK_VERTEXSHADER_H

#include "Shader.h"



class VertexShader : public Shader {
public:
    explicit VertexShader(std::string file);
    const char* Error() override;
};


#endif //LK_VERTEXSHADER_H
