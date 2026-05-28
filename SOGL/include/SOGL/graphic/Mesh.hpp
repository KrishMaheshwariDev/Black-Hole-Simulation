#pragma once

#include <cstddef>

#include "MeshData.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"

namespace SOGL
{
    class Mesh
    {
    public:
        Mesh(const MeshData& meshData);

        ~Mesh() = default;

    public:
        void Bind() const;
        void Unbind() const;

        void Draw() const;

    public:
        [[nodiscard]]
        size_t GetVertexCount() const;

        [[nodiscard]]
        size_t GetIndexCount() const;

        [[nodiscard]]
        bool HasIndices() const;

    private:
        void UploadMeshData(const MeshData& meshData);

        void SetupVertexAttributes();

    private:
        VertexArray m_VAO;

        Buffer m_VBO;
        Buffer m_EBO;

    private:
        size_t m_VertexCount {0};
        size_t m_IndexCount  {0};

        bool m_HasIndices {false};
    };
}