#pragma once

#include <glad/glad.h>
#include <iostream>

class VertexArray {
    private:
        GLuint id;

    public:
        VertexArray();
        ~VertexArray();
        
        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;
        
        VertexArray(VertexArray&& other) noexcept;
        VertexArray& operator=(VertexArray&& other) noexcept;

        void bind() const;

        void AddAttribute(
            GLuint index,
            GLint size,
            GLenum type,
            GLboolean normalized,
            GLsizei stride,
            const void* offset
        );
};