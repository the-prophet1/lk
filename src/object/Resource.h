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

    /*      Save all matrices through an array      */
    Resource &PushVBOValue(Matrix<float> &matrix);

    Resource &PushVBOValue(Matrix<float> &&matrix);

    /* only one EBO matrix */
    Resource &SetEBOValue(Matrix<int> &matrix);

    Resource &SetEBOValue(Matrix<int> &&matrix);

    /* Save all Texture through an array */
    Resource &PushTexture(const std::string &file);

    /* CPU memory move to GPU memory */
    Resource &Apply();

    unsigned int GetVaoID() const;

    unsigned int GetVboID() const;

    unsigned int GetEboID() const;

    const  std::vector<Matrix<float>>& GetVaos() const;

    const std::vector<unsigned int> &GetTextureIDs() const;

    const char *Error();

    const Matrix<int> &GetIndices() const;

private:
    Resource &unbindVBO();

    Resource &bindVBO();

    Resource &bindEBO();

    Resource &bindTexture(unsigned int id);

    Resource &unbindTexture();

    Resource &applyVAO();

private:
    unsigned int vao{};
    unsigned int vbo{};
    unsigned int ebo{};
    std::vector<unsigned int> textureIDs;

    std::vector<Matrix<float>> matrices{};
    Matrix<int> indices{};
    std::vector<Texture> textures;

    string error{};
};


#endif //LK_RESOURCE_H
