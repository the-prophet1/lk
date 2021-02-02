#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include "Resource.h"

Resource::Resource() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

}

Resource &Resource::bindVBO() {
    if (!error.empty()) {
        return *this;
    }
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    return *this;
}

Resource &Resource::applyVAO() {
    if (!error.empty()) {
        return *this;
    }

    std::vector<float> buffer;
    for (auto &m : matrices) {
        buffer.insert(buffer.end(), m.GetM().begin(), m.GetM().end());
    }

    bindVBO();
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(), GL_STATIC_DRAW);
    if (!indices.Empty()) {
        bindEBO();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.ByteSize(), indices.Data(), GL_STATIC_DRAW);
    }

    int index = 0;
    for (int i = 0; i < matrices.size(); ++i) {
        glVertexAttribPointer(i, matrices[i].Column(), GL_FLOAT, GL_FALSE, 0, (void *) index);
        glEnableVertexAttribArray(i);
        index += matrices[i].ByteSize();
    }
    unbindVBO();
    return *this;
}


Resource &Resource::unbindVBO() {
    if (!error.empty()) {
        return *this;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return *this;
}

Resource &Resource::SetEBOValue(Matrix<int> &matrix) {
    if (!error.empty()) {
        return *this;
    }
    indices = matrix;
    return *this;
}

Resource &Resource::SetEBOValue(Matrix<int> &&matrix) {
    return SetEBOValue(matrix);
}

Resource &Resource::bindEBO() {
    if (!error.empty()) {
        return *this;
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    return *this;
}

Resource &Resource::PushVBOValue(Matrix<float> &matrix) {
    if (!error.empty()) {
        return *this;
    }
    matrices.push_back(matrix);
    return *this;
}

Resource &Resource::PushVBOValue(Matrix<float> &&matrix) {
    if (!error.empty()) {
        return *this;
    }
    PushVBOValue(matrix);
    return *this;
}

unsigned int Resource::GetVaoID() const {
    return vao;
}

unsigned int Resource::GetVboID() const {
    return vbo;
}

unsigned int Resource::GetEboID() const {
    return ebo;
}

Resource &Resource::Apply() {
    if (!error.empty()) {
        return *this;
    }
    //apply VAO
    if (!matrices.empty()) {
        applyVAO();
        if (!error.empty()) {
            return *this;
        }
    }

    return *this;
}

Resource &Resource::PushTexture(const string &file) {
    Texture texture;
    if (!texture.Load(file)) {
        error = "can't load file";
        return *this;
    }
    unsigned int textureID;
    glGenTextures(1, &textureID);
    bindTexture(textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);
    glGenerateMipmap(GL_TEXTURE_2D);
    unbindTexture();
    textureIDs.push_back(textureID);

    return *this;
}

const char *Resource::Error() {
    return error.c_str();
}

Resource &Resource::bindTexture(unsigned int id) {
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, id);
    return *this;
}

Resource &Resource::unbindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    return *this;
}

const Matrix<int> &Resource::GetIndices() const {
    return indices;
}

Resource::~Resource() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    for (unsigned int &textureID : textureIDs) {
        glad_glDeleteTextures(1, &textureID);
    }
}

const std::vector<unsigned int> &Resource::GetTextureIDs() const {
    return textureIDs;
}

const std::vector<Matrix<float>>& Resource::GetVaos() const {
    return matrices;
}