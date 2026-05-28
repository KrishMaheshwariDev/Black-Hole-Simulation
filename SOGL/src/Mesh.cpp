#include "../include/SOGL/graphic/Mesh.hpp"

#include <glad/glad.h>

#include <cstddef>

namespace SOGL
{
    Mesh::Mesh(const MeshData& meshData)
        : m_VBO(GL_ARRAY_BUFFER),
          m_EBO(GL_ELEMENT_ARRAY_BUFFER)
    {
        UploadMeshData(meshData);
        SetupVertexAttributes();
    }

    void Mesh::Bind() const
    {
        m_VAO.bind();
    }

    void Mesh::Unbind() const
    {
        m_VAO.unbind();
    }

    void Mesh::Draw() const
    {
        Bind();

        if (m_HasIndices)
        {
            glDrawElements(
                GL_TRIANGLES,
                static_cast<GLsizei>(m_IndexCount),
                GL_UNSIGNED_INT,
                nullptr
            );
        }
        else
        {
            glDrawArrays(
                GL_TRIANGLES,
                0,
                static_cast<GLsizei>(m_VertexCount)
            );
        }
    }

    size_t Mesh::GetVertexCount() const
    {
        return m_VertexCount;
    }

    size_t Mesh::GetIndexCount() const
    {
        return m_IndexCount;
    }

    bool Mesh::HasIndices() const
    {
        return m_HasIndices;
    }

    void Mesh::UploadMeshData(const MeshData& meshData)
    {
        m_VertexCount = meshData.GetVertexCount();
        m_IndexCount  = meshData.GetIndexCount();
        m_HasIndices  = meshData.HasIndices();

        m_VAO.bind();

        m_VBO.bind();

        m_VBO.SetData(
            meshData.GetVertices().data(),
            meshData.GetVertices().size() * sizeof(MeshData::VertexType),
            GL_STATIC_DRAW
        );

        if (m_HasIndices)
        {
            m_EBO.bind();

            m_EBO.SetData(
                meshData.GetIndices().data(),
                meshData.GetIndices().size() * sizeof(MeshData::IndexType),
                GL_STATIC_DRAW
            );
        }
    }

    void Mesh::SetupVertexAttributes()
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