#pragma once

#include <glad/glad.h>
#include "../shaders/Shader.hpp"
#include "Mesh.hpp"

class Renderer{
    public:
        static void Draw(const Mesh& mesh, const Shader& shader);
};