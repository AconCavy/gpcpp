#include "VertexArray.hpp"

#include <gl/glew.h>

using namespace gpcpp::c05;

VertexArray::VertexArray(const float *Vertices, unsigned int NumberOfVertices,
                         const unsigned int *Indices,
                         unsigned int NumberOfIndices)
    : NumberOfVertices(NumberOfVertices), NumberOfIndices(NumberOfIndices) {
  glGenVertexArrays(1, &Array);
  glBindVertexArray(Array);

  glGenBuffers(1, &VertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, NumberOfVertices * 5 * sizeof(float), Vertices,
               GL_STATIC_DRAW);

  glGenBuffers(1, &IndexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumberOfIndices * sizeof(unsigned int),
               Indices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
                        reinterpret_cast<void *>(sizeof(float) * 3));
}

VertexArray::~VertexArray() {
  glDeleteBuffers(1, &VertexBuffer);
  glDeleteBuffers(1, &IndexBuffer);
  glDeleteVertexArrays(1, &Array);
}

void VertexArray::setActive() const { glBindVertexArray(Array); }
