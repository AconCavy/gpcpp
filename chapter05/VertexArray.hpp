#ifndef GPCPP_CHAPTER05_VERTEXARRAY_HPP
#define GPCPP_CHAPTER05_VERTEXARRAY_HPP

namespace gpcpp::c05 {

class VertexArray {
public:
  VertexArray(const float *Vertices, unsigned int NumberOfVertices,
              const unsigned int *Indices, unsigned int NumberOfIndices);
  ~VertexArray();

  void setActive() const;

  [[nodiscard]] unsigned int getNumberOfIndices() const {
    return NumberOfIndices;
  }
  [[nodiscard]] unsigned int getNumberOfVertices() const {
    return NumberOfVertices;
  }

private:
  unsigned int NumberOfVertices;
  unsigned int NumberOfIndices;
  unsigned int VertexBuffer{};
  unsigned int IndexBuffer{};
  unsigned int Array{};
};

} // namespace gpcpp::c05

#endif // GPCPP_CHAPTER05_VERTEXARRAY_HPP
