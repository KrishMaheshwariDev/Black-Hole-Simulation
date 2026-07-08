#include "Camera2D.hpp"

#include <algorithm>

#include <glm/ext/matrix_clip_space.hpp>

#include "Config.hpp"

namespace
{
    bool IsPressed(GLFWwindow* window, int key)
    {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }
}

Camera2D::Camera2D()
    : m_Zoom(Config::Camera::kDefaultZoom),
      m_WasZoomInPressed(false),
      m_WasZoomOutPressed(false)
{
}

void Camera2D::UpdateFromInput(GLFWwindow* window)
{
    const bool isZoomInPressed = IsPressed(window, GLFW_KEY_KP_ADD);
    const bool isZoomOutPressed = IsPressed(window, GLFW_KEY_KP_SUBTRACT);

    if (isZoomInPressed && !m_WasZoomInPressed)
    {
        m_Zoom = std::min(
            m_Zoom * Config::Camera::kZoomMultiplierPerStep,
            Config::Camera::kMaximumZoom
        );
    }

    if (isZoomOutPressed && !m_WasZoomOutPressed)
    {
        m_Zoom = std::max(
            m_Zoom / Config::Camera::kZoomMultiplierPerStep,
            Config::Camera::kMinimumZoom
        );
    }

    m_WasZoomInPressed = isZoomInPressed;
    m_WasZoomOutPressed = isZoomOutPressed;
}

glm::mat4 Camera2D::CreateProjection(int width, int height) const
{
    if (height == 0)
    {
        height = 1;
    }

    const float aspect =
        static_cast<float>(width) /
        static_cast<float>(height);

    const float verticalSpan = 1.0f / m_Zoom;
    const float horizontalSpan = aspect >= 1.0f
        ? aspect * verticalSpan
        : verticalSpan;

    if (aspect >= 1.0f)
    {
        return glm::ortho(
            -horizontalSpan,
             horizontalSpan,
            -verticalSpan,
             verticalSpan,
            -1.0f,
             1.0f
        );
    }

    return glm::ortho(
        -horizontalSpan,
         horizontalSpan,
        -verticalSpan / aspect,
         verticalSpan / aspect,
        -1.0f,
         1.0f
    );
}
