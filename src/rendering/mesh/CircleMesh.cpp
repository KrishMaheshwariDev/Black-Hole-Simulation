#include "CircleMesh.hpp"

#include <glm/gtc/type_ptr.hpp>

#include "core/Logger.hpp"
#include "SOGL/graphic/MeshData.hpp"

CircleMesh::CircleMesh(
    float radius,
    unsigned int segments
)
    : mesh(CreateMeshData(radius, segments))
{}

void CircleMesh::draw(const SOGL::Shader& shader, const Transform& transform) const{
    shader.use();
    shader.setMat4(
        "uModel",
        glm::value_ptr(transform.GetMatrix())
    );

    mesh.Draw();
    Core::Logger::LogOpenGLErrors("CircleMesh", "mesh draw");
}

SOGL::MeshData CircleMesh::CreateMeshData(float radius, unsigned int segments){
    std::vector<SOGL::StaticVertex> vertices;
    std::vector<uint32_t> indices;

    vertices.reserve(segments + 1);
    indices.reserve(segments * 3);

    // Center vertex
    SOGL::StaticVertex centerVertex;
    centerVertex.position = {0.0f, 0.0f, 0.0f};

    vertices.push_back(centerVertex);

    const float angleStep =
        (2.0f * std::numbers::pi_v<float>) /
        static_cast<float>(segments);

    // Outer vertices
    for (unsigned int i = 0; i < segments; i++)
    {
        float angle = static_cast<float>(i) * angleStep;

        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);

        SOGL::StaticVertex vertex;
        vertex.position = {x, y, 0.0f};

        vertices.push_back(vertex);
    }

    // Triangle fan indices
    for (uint32_t i = 1; i < segments; i++)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    // Closing triangle
    indices.push_back(0);
    indices.push_back(segments);
    indices.push_back(1);

    return SOGL::MeshData(
        std::move(vertices),
        std::move(indices)
    );
}
