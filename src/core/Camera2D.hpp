#pragma once

#include <glfw/glfw3.h>
#include <glm/mat4x4.hpp>

class Camera2D
{
public:
    Camera2D();

    void UpdateFromInput(GLFWwindow* window);

    [[nodiscard]]
    glm::mat4 CreateProjection(int width, int height) const;

private:
    float m_Zoom;
    bool m_WasZoomInPressed;
    bool m_WasZoomOutPressed;
};
