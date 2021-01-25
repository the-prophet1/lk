#include <glad/glad.h>
#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &veo);
}

VAO &VAO::BindVBO() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    return *this;
}

VAO &VAO::SetVBOValue() {
    std::vector<float> buffer;
    for (auto &m : matrices) {
        buffer.insert(buffer.end(), m.GetM().begin(), m.GetM().end());
    }

    this->BindVBO();
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(), GL_STATIC_DRAW);
    int index = 0;
    for (int i = 0; i < matrices.size(); ++i) {
        glVertexAttribPointer(i, matrices[i].Column(), GL_FLOAT, GL_FALSE, 0, (void *) index);
        glEnableVertexAttribArray(i);
        index += matrices[i].ByteSize();
    }
    this->UnbindVBO();
    return *this;
}


VAO &VAO::UnbindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return *this;
}

VAO &VAO::SetVEOValue(Matrix<int> &matrix) {
    indices = matrix;
    this->BindVEO();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.ByteSize(), indices.Data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, matrix.Column(), GL_FLOAT, GL_FALSE, 0, (void *) nullptr);
    return *this;
}

VAO &VAO::SetVEOValue(Matrix<int> &&matrix) {
    return SetVEOValue(matrix);
}

VAO &VAO::BindVEO() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
    return *this;
}

VAO &VAO::UnbindVEO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return *this;
}

VAO &VAO::DrawElemTriangle() {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.Row() * indices.Column(), GL_UNSIGNED_INT, nullptr);
    return *this;
}

VAO &VAO::PushVBOValue(Matrix<float> &matrix) {
    matrices.push_back(matrix);
    return *this;
}

VAO &VAO::PushVBOValue(Matrix<float> &&matrix) {
    PushVBOValue(matrix);
    return *this;
}

unsigned int VAO::GetVaoId() const {
    return vao;
}
