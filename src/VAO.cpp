#include <glad/glad.h>
#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1,&vbo);
}

void VAO::Bind() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VAO::DrawTriangle() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void VAO::SetValue() {
    this->Bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices2, GL_STATIC_DRAW);
}
