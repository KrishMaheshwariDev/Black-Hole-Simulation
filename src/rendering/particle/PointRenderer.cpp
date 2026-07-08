#include "PointRenderer.hpp"

#include <algorithm>
#include <array>
#include <cstddef>

#include "core/Logger.hpp"

PointRenderer::PointRenderer()
    : m_VAO(),
      m_VBO(GL_ARRAY_BUFFER)
{
    m_VAO.bind();
    m_VBO.bind();

    m_VAO.AddAttribute(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(PointVertex),
        reinterpret_cast<const void*>(offsetof(PointVertex, position))
    );

    m_VAO.AddAttribute(
        1,
        1,
        GL_FLOAT,
        GL_FALSE,
        sizeof(PointVertex),
        reinterpret_cast<const void*>(offsetof(PointVertex, alpha))
    );

    m_VAO.AddAttribute(
        2,
        1,
        GL_FLOAT,
        GL_FALSE,
        sizeof(PointVertex),
        reinterpret_cast<const void*>(offsetof(PointVertex, size))
    );

    m_VBO.unbind();
    m_VAO.unbind();
}

void PointRenderer::DrawParticle(
    const SOGL::Shader& shader,
    const glm::vec2& position,
    float size,
    const glm::vec4& color
)
{
    const std::array<PointVertex, 1> vertices{{
        PointVertex{
            .position = position,
            .alpha = 1.0f,
            .size = size
        }
    }};

    shader.use();
    shader.setVec4("uColor", color.r, color.g, color.b, color.a);
    shader.setFloat("uRenderAsPoint", 1.0f);

    m_VAO.bind();
    m_VBO.bind();
    m_VBO.SetData(vertices.data(), sizeof(PointVertex), GL_DYNAMIC_DRAW);

    glDrawArrays(GL_POINTS, 0, 1);

    m_VBO.unbind();
    m_VAO.unbind();
    Core::Logger::LogOpenGLErrors("PointRenderer", "particle draw");
}

void PointRenderer::DrawTrail(
    const SOGL::Shader& shader,
    const std::vector<TrailPoint>& trail,
    float trailLifetimeSeconds,
    float headSize,
    const glm::vec4& color
)
{
    if (trail.empty() || trailLifetimeSeconds <= 0.0f)
    {
        return;
    }

    std::vector<PointVertex> vertices;
    vertices.reserve(trail.size());

    for (std::size_t index = 0; index < trail.size(); ++index)
    {
        const auto& point = trail[index];
        const float normalizedAge = std::clamp(
            point.ageSeconds / trailLifetimeSeconds,
            0.0f,
            1.0f
        );
        const float normalizedIndex =
            trail.size() > 1
                ? static_cast<float>(index) / static_cast<float>(trail.size() - 1)
                : 1.0f;
        const float fadeAlpha =
            (1.0f - normalizedAge) *
            std::clamp(normalizedIndex * normalizedIndex, 0.0f, 1.0f);

        vertices.push_back(
            PointVertex{
                .position = point.position,
                .alpha = fadeAlpha,
                .size = headSize
            }
        );
    }

    shader.use();
    shader.setVec4("uColor", color.r, color.g, color.b, color.a);
    shader.setFloat("uRenderAsPoint", 0.0f);

    m_VAO.bind();
    m_VBO.bind();
    m_VBO.SetData(
        vertices.data(),
        vertices.size() * sizeof(PointVertex),
        GL_DYNAMIC_DRAW
    );

    glLineWidth(std::max(1.0f, headSize * 0.35f));
    glDrawArrays(GL_LINE_STRIP, 0, static_cast<GLsizei>(vertices.size()));

    m_VBO.unbind();
    m_VAO.unbind();
    Core::Logger::LogOpenGLErrors("PointRenderer", "trail draw");
}
