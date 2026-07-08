#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Config.hpp"
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

    float pointSize{Config::Particles::kDefaultPointSize};
    glm::vec4 color{Config::Particles::kDefaultColor};
    float collisionRadius{0.0f};

    float lifetimeSeconds{Config::Particles::kDefaultLifetimeSeconds};
    float ageSeconds{0.0f};

    float trailLifetimeSeconds{Config::Particles::kDefaultTrailLifetimeSeconds};
    std::size_t maxTrailPoints{Config::Particles::kDefaultMaxTrailPoints};
    std::vector<TrailPoint> trail;

    LightParticle(
        float initialPointSize,
        Transform initialTransform = {},
        PhysicsBody initialPhysics = {},
        glm::vec4 initialColor = Config::Particles::kDefaultColor,
        float initialCollisionRadius = 0.0f
    )
        : transform(initialTransform),
          physics(initialPhysics),
          pointSize(initialPointSize),
          color(initialColor),
          collisionRadius(initialCollisionRadius)
    {
        RecordTrailPoint();
    }

    void RecordTrailPointIfNeeded(float minimumDistance)
    {
        if (trail.empty())
        {
            RecordTrailPoint();
            return;
        }

        const glm::vec2 offset = transform.position - trail.back().position;
        if (glm::length(offset) >= minimumDistance)
        {
            RecordTrailPoint();
        }
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
