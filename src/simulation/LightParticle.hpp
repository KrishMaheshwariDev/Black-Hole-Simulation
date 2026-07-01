#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "SimulationComponents.hpp"

struct TrailPoint
{
    glm::vec2 position{0.0f, 0.0f};
    float ageSeconds{0.0f};
};

struct LightParticle
{
    Transform transform;
    PhysicsBody physics;

    float pointSize{8.0f};
    glm::vec4 color{1.0f, 0.95f, 0.7f, 1.0f};

    float lifetimeSeconds{5.0f};
    float ageSeconds{0.0f};

    float trailLifetimeSeconds{1.0f};
    std::size_t maxTrailPoints{24};
    std::vector<TrailPoint> trail;

    LightParticle(
        float initialPointSize,
        Transform initialTransform = {},
        PhysicsBody initialPhysics = {},
        glm::vec4 initialColor = {1.0f, 0.95f, 0.7f, 1.0f}
    )
        : transform(initialTransform),
          physics(initialPhysics),
          pointSize(initialPointSize),
          color(initialColor)
    {
        RecordTrailPoint();
    }

    void RecordTrailPoint()
    {
        trail.push_back(TrailPoint{.position = transform.position, .ageSeconds = 0.0f});

        if (trail.size() > maxTrailPoints)
        {
            trail.erase(
                trail.begin(),
                trail.begin() + static_cast<std::ptrdiff_t>(trail.size() - maxTrailPoints)
            );
        }
    }

    void UpdateTrail(float deltaTime)
    {
        ageSeconds += deltaTime;

        for (auto& point : trail)
        {
            point.ageSeconds += deltaTime;
        }

        trail.erase(
            std::remove_if(
                trail.begin(),
                trail.end(),
                [this](const TrailPoint& point)
                {
                    return point.ageSeconds > trailLifetimeSeconds;
                }
            ),
            trail.end()
        );
    }
};
