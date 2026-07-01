#pragma once

#include <SOGL/shaders/Shader.hpp>

#include "rendering/mesh/CircleMesh.hpp"
#include "SimulationComponents.hpp"

struct BlackHole
{
    CircleMesh geometry;
    Transform transform;
    PhysicsBody physics;

    float eventHorizonRadius {1.0f};

    BlackHole(
        float radius,
        unsigned int segments,
        Transform initialTransform = {},
        PhysicsBody initialPhysics = {},
        float initialEventHorizonRadius = 1.0f
    )
        : geometry(radius, segments),
          transform(initialTransform),
          physics(initialPhysics),
          eventHorizonRadius(initialEventHorizonRadius)
    {
    }

    void Draw(const SOGL::Shader& shader) const
    {
        geometry.draw(shader, transform);
    }
};
