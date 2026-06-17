// #include <vector>
// #include <cmath>
// #include <cstdint>
#include <windows.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <SOGL/window/Window.hpp>
#include <SOGL/graphic/Renderer.hpp>
#include <SOGL/shaders/Shader.hpp>

#include "rendering/mesh/CircleMesh.hpp"


/*
For Nvidia GPU based renderering
Currently capped at 144 FPS, possible reason of the cap/limit is might be the refresh rate of the screen
Screen have 144Hz refresh rate
*/ 
#ifdef _WIN32
extern "C" {
    // Force NVIDIA Optimus to use the discrete GPU
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    // Force AMD PowerXpress to use the discrete GPU
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif     

/*
namespace Pollution, TODO: remove the SOGL namespace before deployment, use standard SOGL::
*/
using namespace SOGL;

glm::mat4 CreateProjection(int width, int height){
    if(height == 0){
        height = 1;
    }
    float aspect =
        static_cast<float>(width) /
        static_cast<float>(height);

    if(aspect >= 1.0f)
    {
        return glm::ortho(
            -aspect,
             aspect,
            -1.0f,
             1.0f,
            -1.0f,
             1.0f
        );
    }

    return glm::ortho(
        -1.0f,
         1.0f,
        -1.0f / aspect,
         1.0f / aspect,
        -1.0f,
         1.0f
    );
}

int main() {
    // Initialize the window
    Window window(1280, 720, "SOGL Example");
    Shader shader("../assets/shaders/basic.vert", "../assets/shaders/basic.frag");

    CircleMesh circle(0.5f, 64);

    // FPS counter
    double fpsTimer = glfwGetTime();
    int frameCount = 0;

    while(!window.shouldClose()){

        // FPS updates (per second)
        frameCount++;
        double now = glfwGetTime();

        if(now - fpsTimer >= 1.0){
            std::string title =
                "Black Hole Simulation | FPS: "
                + std::to_string(frameCount);

            glfwSetWindowTitle(window.getNativeWindow(),
                                title.c_str());

            frameCount = 0;
            fpsTimer = now;
        }

        // Window and Rendering
        window.pollEvents();
        glClearColor(
            0.1f,
            0.1f,
            0.1f,
            1.0f
        );
        window.clearColor();
        shader.use();

        // Projection Handling for Window Resize
        int width, height;
        glfwGetFramebufferSize(
            window.getNativeWindow(),
            &width,
            &height
        );

        glViewport(0, 0, width, height);

        glm::mat4 projection =
            CreateProjection(width, height);

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.getID(),
                "uProjection"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        // Element or Object Rendering Calls
        circle.draw();
        window.swapBuffers();
    }
    return 0;
}