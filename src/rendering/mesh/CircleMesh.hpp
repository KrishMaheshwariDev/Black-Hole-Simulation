#pragma once

#include <vector>
#include <cmath>
#include <SOGL/graphic/Mesh.hpp>

class CircleMesh
{
public:
    CircleMesh(float radius, unsigned int segments);

    void draw();

private:
    SOGL::Mesh mesh;

    static SOGL::MeshData CreateMeshData(float radius, unsigned int segments);
};