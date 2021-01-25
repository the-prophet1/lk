#ifndef LK_VAO_H
#define LK_VAO_H

#include "../tool/Matrix.hpp"

enum ObjectType {
    VBOType,
    VEOType,
};

class VAO {
public:
    VAO();

    VAO &PushVBOValue(Matrix<float> &matrix);

    VAO &PushVBOValue(Matrix<float> &&matrix);

    VAO &SetVBOValue();

    VAO &SetVEOValue(Matrix<int> &matrix);

    VAO &SetVEOValue(Matrix<int> &&matrix);

    VAO &DrawElemTriangle();

    unsigned int GetVaoId() const;

private:
    VAO &BindVBO();

    VAO &UnbindVBO();

    VAO &BindVEO();

    VAO &UnbindVEO();


private:
    unsigned int vao{};
    unsigned int vbo{};
    unsigned int veo{};
    std::vector<Matrix<float>> matrices{};

    Matrix<int> indices{};
};


#endif //LK_VAO_H
