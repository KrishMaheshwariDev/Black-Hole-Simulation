#pragma once

#include <vector>
#include <cstdint>
#include "VertexTypes.hpp"

namespace SOGL
{
    class MeshData
    {
    public:
        using VertexType = StaticVertex;
        using IndexType  = uint32_t;

    public:
        MeshData() = default;

        MeshData(
            const std::vector<VertexType>& vertices,
            const std::vector<IndexType>& indices
        );

        MeshData(
            std::vector<VertexType>&& vertices,
            std::vector<IndexType>&& indices
        );

    public:
        [[nodiscard]]
        const std::vector<VertexType>& GetVertices() const;

        [[nodiscard]]
        const std::vector<IndexType>& GetIndices() const;

        [[nodiscard]]
        size_t GetVertexCount() const;

        [[nodiscard]]
        size_t GetIndexCount() const;

        [[nodiscard]]
        bool HasIndices() const;

        [[nodiscard]]
        bool Empty() const;

    private:
        std::vector<VertexType> m_Vertices;
        std::vector<IndexType>  m_Indices;
    };
}