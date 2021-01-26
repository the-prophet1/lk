#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include "Resource.h"

Resource::Resource() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenTextures(1, &textureID);
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
    bindEBO();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.ByteSize(), indices.Data(), GL_STATIC_DRAW);

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

unsigned int Resource::GetTextureID() const {
    return textureID;
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

    if (!texture.Empty()) {
        applyTexture();
    }

    return *this;
}

Resource &Resource::SetTexture(const std::string &file) {
    if (!texture.Load(file)) {
        error = "can't load file";
        return *this;
    }
    return *this;
}

const char *Resource::Error() {
    return error.c_str();
}

Resource &Resource::applyTexture() {
    bindTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);
    glGenerateMipmap(GL_TEXTURE_2D);
    unbindTexture();
    return *this;
}

Resource &Resource::bindTexture() {
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, textureID);
    return *this;
}

Resource &Resource::unbindTexture() {
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return *this;
}

const Matrix<int> &Resource::GetIndices() const {
    return indices;
}

Resource::~Resource() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glad_glDeleteTextures(1, &textureID);
}
