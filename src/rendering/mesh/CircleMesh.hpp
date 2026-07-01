#pragma once

#include <vector>
#include <cmath>
#include <SOGL/graphic/Mesh.hpp>
#include <SOGL/shaders/Shader.hpp>

#include "simulation/SimulationComponents.hpp"

class CircleMesh
{
public:
    CircleMesh(float radius, unsigned int segments);

    void draw(const SOGL::Shader& shader, const Transform& transform) const;

private:
    SOGL::Mesh mesh;

    static SOGL::MeshData CreateMeshData(float radius, unsigned int segments);
};
