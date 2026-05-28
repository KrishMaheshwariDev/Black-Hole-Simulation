#include "../include/SOGL/graphic/VertexLayout.hpp"

#include <glad/glad.h>

#include <cstddef>

namespace SOGL
{
    void VertexLayout::ApplyStaticVertexLayout()
    {
        constexpr GLsizei stride = sizeof(StaticVertex);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<void*>(offsetof(StaticVertex, position))
        );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<void*>(offsetof(StaticVertex, normal))
        );

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            2,
            2,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<void*>(offsetof(StaticVertex, uv))
        );

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(
            3,
            3,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<void*>(offsetof(StaticVertex, tangent))
        );
    }
}