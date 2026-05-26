#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include "Buffer.hpp"
#include "VertexArray.hpp"

class Mesh{
    public:
        // Non-Index data
        Mesh(   
            const void* vertexData,
            size_t vertexSize,
            GLsizei vertexCount,
            GLsizei stride
        );

        // Index Data
        Mesh(
            const void* vertexData,
            size_t vertexSize,
            GLsizei vertexCount,
            GLsizei stride,
            const void* indexData,
            size_t indexSize,
            GLsizei indexCount
        );
        void Draw() const;

    private:
        VertexArray VAO;
        Buffer VBO;
        Buffer EBO;

        GLsizei vertexCount;
        GLsizei indexCount;

        GLenum drawMode;
        bool hasIndicies;
};