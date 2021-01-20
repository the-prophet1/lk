#ifndef LK_VAO_H
#define LK_VAO_H

#include "Matrix.hpp"

enum ObjectType {
    VBOType,
    VEOType,
};

class VAO {
public:
    VAO();

    VAO &SetVBOValue(Matrix<float> &matrix);

    VAO &SetVBOValue(Matrix<float> &&matrix);

    VAO &SetVEOValue(Matrix<int> &matrix);

    VAO &SetVEOValue(Matrix<int> &&matrix);

    VAO &DrawTriangle();

    VAO &DrawElemTriangle();

private:
    VAO &BindVBO();
    VAO &UnbindVBO();

    VAO &BindVEO();
    VAO &UnbindVEO();


private:
    unsigned int vao{};
    unsigned int vbo{};
    unsigned int veo{};
    Matrix<float> ma{};
    Matrix<int> indices{};
};


#endif //LK_VAO_H
