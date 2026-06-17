#pragma once

#include "glm/ext/vector_float2.hpp"
#include <glm/vec2.hpp>

struct Transform{
    glm::vec2 position{0.0f, 0.0f};

    float rotation {0.0f};
};

struct PhysicsBody{
    float mass{1.0f};

    glm::vec2 velocity {0.0f, 0.0f};
};