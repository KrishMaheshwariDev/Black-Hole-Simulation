#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace SOGL
{
    struct StaticVertex
    {
        glm::vec3 position {0.0f};
        glm::vec3 normal   {0.0f};
        glm::vec2 uv       {0.0f};
        glm::vec3 tangent  {0.0f};
    };
}