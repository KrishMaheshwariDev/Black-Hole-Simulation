#include <vector>
#include <cmath>
#include <cstdint>

#include <glad/glad.h>
#include <SOGL/window/Window.hpp>
#include <SOGL/graphic/Renderer.hpp>
#include <SOGL/shaders/Shader.hpp>

#include "rendering/mesh/CircleMesh.hpp"

using namespace SOGL;


int main() {
    // Initialize the window
    Window window(1280, 720, "SOGL Example");
    Shader shader("../assets/shaders/basic.vert", "../assets/shaders/basic.frag");

    CircleMesh circle(0.5f, 4);

    while(!window.shouldClose()){
        window.pollEvents();
        glClearColor(
            0.1f,
            0.1f,
            0.1f,
            1.0f
        );
        window.clearColor();
        shader.use();
        circle.draw();
        window.swapBuffers();
    }
    return 0;
}