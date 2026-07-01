#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include "glm/ext/vector_float2.hpp"
#include <glm/vec2.hpp>

struct Transform{
    glm::vec2 position{0.0f, 0.0f};

    float rotation {0.0f};

    glm::vec2 scale{1.0f};

    [[nodiscard]]
    glm::mat4 GetMatrix() const
    {
        glm::mat4 model(1.0f);

        model = glm::translate(model, glm::vec3(position, 0.0f));
        model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(scale, 1.0f));

        return model;
    }
};

struct PhysicsBody{
    float mass{1.0f};

    glm::vec2 velocity {0.0f, 0.0f};

    glm::vec2 accumulatedForce {0.0f, 0.0f};

    bool isStatic {false};

    void AddForce(const glm::vec2& force)
    {
        accumulatedForce += force;
    }

    [[nodiscard]]
    glm::vec2 GetAcceleration() const
    {
        if (isStatic || mass <= 0.0f)
        {
            return {0.0f, 0.0f};
        }

        return accumulatedForce / mass;
    }

    void ClearForces()
    {
        accumulatedForce = {0.0f, 0.0f};
    }
};
