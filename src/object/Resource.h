#ifndef LK_RESOURCE_H
#define LK_RESOURCE_H

#include "../tool/Matrix.hpp"
#include "../texture/Texture.h"
#include <string>

enum ObjectType {
    VBOType,
    VEOType,
};

typedef std::string string;

class Resource {

public:
    Resource();

    ~Resource();

    Resource &PushVBOValue(Matrix<float> &matrix);

    Resource &PushVBOValue(Matrix<float> &&matrix);

    Resource &SetEBOValue(Matrix<int> &matrix);

    Resource &SetEBOValue(Matrix<int> &&matrix);

    Resource &SetTexture(const std::string &file);

    Resource &Apply();

    unsigned int GetVaoID() const;

    unsigned int GetVboID() const;

    unsigned int GetEboID() const;

    unsigned int GetTextureID() const;

    const char *Error();

    const Matrix<int>& GetIndices() const;

private:
    Resource &unbindVBO();

    Resource &bindVBO();

    Resource &bindEBO();

    Resource &bindTexture();

    Resource &unbindTexture();

    Resource &applyVAO();

    Resource &applyTexture();


private:
    unsigned int vao{};
    unsigned int vbo{};
    unsigned int ebo{};
    unsigned int textureID{};

    std::vector<Matrix<float>> matrices{};
    Matrix<int> indices{};
    Texture texture;

    string error{};
};


#endif //LK_RESOURCE_H
