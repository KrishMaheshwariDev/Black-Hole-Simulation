#pragma once

#include <SOGL/shaders/Shader.hpp>

#include "rendering/mesh/CircleMesh.hpp"
#include "SimulationComponents.hpp"

struct Planet
{
    CircleMesh geometry;
    Transform transform;
    PhysicsBody physics;
    float collisionRadius{0.08f};

    Planet(
        float radius,
        unsigned int segments,
        Transform initialTransform = {},
        PhysicsBody initialPhysics = {},
        float initialCollisionRadius = 0.08f
    )
        : geometry(radius, segments),
          transform(initialTransform),
          physics(initialPhysics),
          collisionRadius(initialCollisionRadius)
    {
    }

    void Draw(const SOGL::Shader& shader) const
    {
        geometry.draw(shader, transform);
    }
};
