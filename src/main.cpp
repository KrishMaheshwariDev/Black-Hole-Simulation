#include <vector>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>

#include <SOGL/window/Window.hpp>
#include <SOGL/shaders/Shader.hpp>

#include <SOGL/graphic/Mesh.hpp>
#include <SOGL/graphic/MeshData.hpp>
#include <SOGL/graphic/VertexTypes.hpp>
#include <SOGL/graphic/Renderer.hpp>

using namespace SOGL;

MeshData GenerateCircle(float radius, uint32_t segments)
{
    std::vector<StaticVertex> vertices;
    std::vector<uint32_t> indices;

    vertices.push_back({
        .position = glm::vec3(0.0f, 0.0f, 0.0f),
        .normal   = glm::vec3(0.0f, 0.0f, 1.0f),
        .uv       = glm::vec2(0.5f, 0.5f),
        .tangent  = glm::vec3(1.0f, 0.0f, 0.0f)
    });

    const float step =
        (2.0f * glm::pi<float>()) / static_cast<float>(segments);

    for(uint32_t i = 0; i <= segments; i++)
    {
        float angle = i * step;

        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);

        vertices.push_back({
            .position = glm::vec3(x, y, 0.0f),
            .normal   = glm::vec3(0.0f, 0.0f, 1.0f),
            .uv       = glm::vec2(
                (x / radius + 1.0f) * 0.5f,
                (y / radius + 1.0f) * 0.5f
            ),
            .tangent  = glm::vec3(1.0f, 0.0f, 0.0f)
        });
    }

    for(uint32_t i = 1; i <= segments; i++)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    return MeshData(
        std::move(vertices),
        std::move(indices)
    );
}

int main()
{
    Window window(800, 800, "Circle Test");

    Shader shader("C:/Kreeece/Projects/BBH/assets/shaders/basic.vert","C:/Kreeece/Projects/BBH/assets/shaders/basic.frag");

    MeshData circleData = GenerateCircle(0.5f, 1000);

    Mesh circleMesh(circleData);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    while(!window.shouldClose())
    {
        window.pollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        Renderer::Draw(circleMesh, shader);

        window.swapBuffers();
    }

    return 0;
}