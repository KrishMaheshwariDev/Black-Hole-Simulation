#pragma once

#include <SOGL/shaders/Shader.hpp>

#include "rendering/mesh/CircleMesh.hpp"
#include "SimulationComponents.hpp"

struct Planet
{
    CircleMesh geometry;
    Transform transform;
    PhysicsBody physics;

    Planet(
        float radius,
        unsigned int segments,
        Transform initialTransform = {},
        PhysicsBody initialPhysics = {}
    )
        : geometry(radius, segments),
          transform(initialTransform),
          physics(initialPhysics)
    {
    }

    void Draw(const SOGL::Shader& shader) const
    {
        geometry.draw(shader, transform);
    }
};
