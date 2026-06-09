#pragma once

#include <glad/glad.h>
#include "../shaders/Shader.hpp"
// #include "Mesh.hpp"

namespace SOGL {
    class Renderer{
        public:
            template<typename T>
            static void Draw(const T mesh, const Shader& shader);
    };
}
