#pragma once

#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <SOGL/graphic/Buffer.hpp>
#include <SOGL/graphic/VertexArray.hpp>
#include <SOGL/shaders/Shader.hpp>

#include "simulation/LightParticle.hpp"

struct PointVertex
{
    glm::vec2 position{0.0f, 0.0f};
    float alpha{1.0f};
    float size{1.0f};
};

class PointRenderer
{
public:
    PointRenderer();

    void DrawParticle(
        const SOGL::Shader& shader,
        const glm::vec2& position,
        float size,
        const glm::vec4& color
    );

    void DrawTrail(
        const SOGL::Shader& shader,
        const std::vector<TrailPoint>& trail,
        float trailLifetimeSeconds,
        float headSize,
        const glm::vec4& color
    );

private:
    SOGL::VertexArray m_VAO;
    SOGL::Buffer m_VBO;
};
