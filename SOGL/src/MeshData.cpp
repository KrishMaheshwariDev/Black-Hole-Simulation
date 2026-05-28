#include "../include/SOGL/graphic/MeshData.hpp"

namespace SOGL
{
    MeshData::MeshData(
        const std::vector<VertexType>& vertices,
        const std::vector<IndexType>& indices
    )
        : m_Vertices(vertices),
          m_Indices(indices)
    {
    }

    MeshData::MeshData(
        std::vector<VertexType>&& vertices,
        std::vector<IndexType>&& indices
    )
        : m_Vertices(std::move(vertices)),
          m_Indices(std::move(indices))
    {
    }

    const std::vector<MeshData::VertexType>&
    MeshData::GetVertices() const
    {
        return m_Vertices;
    }

    const std::vector<MeshData::IndexType>&
    MeshData::GetIndices() const
    {
        return m_Indices;
    }

    size_t MeshData::GetVertexCount() const
    {
        return m_Vertices.size();
    }

    size_t MeshData::GetIndexCount() const
    {
        return m_Indices.size();
    }

    bool MeshData::HasIndices() const
    {
        return !m_Indices.empty();
    }

    bool MeshData::Empty() const
    {
        return m_Vertices.empty();
    }
}