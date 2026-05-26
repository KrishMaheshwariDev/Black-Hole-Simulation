#include "../include/SOGL/graphic/Mesh.hpp"

Mesh::Mesh(const void* vertexData, size_t vertexSize, GLsizei vertexCount, GLsizei stride):
    VBO(GL_ARRAY_BUFFER), EBO(GL_ELEMENT_ARRAY_BUFFER), vertexCount(vertexCount), indexCount(0), drawMode(GL_TRIANGLES), hasIndicies(false){
        VAO.bind();
        VBO.bind();

        VBO.SetData(vertexData, vertexSize, GL_STATIC_DRAW);

        VAO.AddAttribute(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    }

Mesh::Mesh(const void* vertexData,
           size_t vertexSize,
           GLsizei vCount,
           GLsizei stride,
           const void* indexData,
           size_t indexSize,
           GLsizei iCount)
    : VBO(GL_ARRAY_BUFFER),
      EBO(GL_ELEMENT_ARRAY_BUFFER),
      vertexCount(vCount),
      indexCount(iCount),
      drawMode(GL_TRIANGLES),
      hasIndicies(true){
        VAO.bind();

        VBO.bind();
        VBO.SetData(vertexData, vertexSize, GL_STATIC_DRAW);
        EBO.bind();
        EBO.SetData(indexData, indexSize, GL_STATIC_DRAW);

        VAO.AddAttribute(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
      }

void Mesh::Draw() const{
    VAO.bind();

    if(hasIndicies){
        glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, nullptr);
    }
    else{
        glDrawArrays(drawMode, 0, vertexCount);
    }
}