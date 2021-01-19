#ifndef LK_VAO_H
#define LK_VAO_H

#include "VBO.h"

class VAO {
public:
    VAO();
    void Bind();
    void SetValue();

    void DrawTriangle();

private:
    unsigned int vao{};
    unsigned int vbo{};
};


#endif //LK_VAO_H
