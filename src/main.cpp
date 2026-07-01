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

#include "core/Logger.hpp"
#include "core/TickSystem.hpp"
#include "rendering/particle/PointRenderer.hpp"
#include "simulation/PhysicsSystem.hpp"
#include "simulation/SimulationWorld.hpp"

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
    Core::Logger::Info("Main", "Starting Black Hole Simulation");

    Window window(1280, 720, "SOGL Example");
    Shader shader("../assets/shaders/basic.vert", "../assets/shaders/basic.frag");
    Shader particleShader("../assets/shaders/particle.vert", "../assets/shaders/particle.frag");
    PointRenderer pointRenderer;
    FixedTimestep fixedTimestep(20.0f);
    PhysicsSystem physicsSystem;
    SimulationWorld world;

    world.blackHoles.emplace_back(
        0.22f,
        64,
        Transform{
            .position = {0.0f, 0.0f},
            .rotation = 0.0f,
            .scale = {1.0f, 1.0f}
        },
        PhysicsBody{
            .mass = 1000.0f,
            .velocity = {0.0f, 0.0f},
            .accumulatedForce = {0.0f, 0.0f},
            .isStatic = true
        },
        0.22f
    );

    world.planets.emplace_back(
        0.08f,
        64,
        Transform{
            .position = {-0.7f, 0.2f},
            .rotation = 0.0f,
            .scale = {1.0f, 1.0f}
        },
        PhysicsBody{
            .mass = 10.0f,
            .velocity = {0.35f, 0.0f}
        }
    );

    world.lightParticles.emplace_back(
        5.0f,
        Transform{
            .position = {-0.25f, -0.45f},
            .rotation = 0.0f,
            .scale = {1.0f, 1.0f}
        },
        PhysicsBody{
            .mass = 0.1f,
            .velocity = {0.6f, 0.25f}
        },
        glm::vec4{1.0f, 0.95f, 0.7f, 1.0f}
    );

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

        fixedTimestep.update();

        while (fixedTimestep.HasPendingTick())
        {
            physicsSystem.Update(
                world,
                fixedTimestep.GetFixedDeltaTime()
            );

            fixedTimestep.ConsumeTick();
        }

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

        shader.use();
        shader.setMat4("uProjection", glm::value_ptr(projection));
        Core::Logger::LogOpenGLErrors("Main", "basic shader projection upload");

        particleShader.use();
        particleShader.setMat4("uProjection", glm::value_ptr(projection));
        Core::Logger::LogOpenGLErrors("Main", "particle shader projection upload");

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_PROGRAM_POINT_SIZE);
        Core::Logger::LogOpenGLErrors("Main", "frame render state setup");

        // Element or Object Rendering Calls
        for (const auto& blackHole : world.blackHoles)
        {
            blackHole.Draw(shader);
        }

        for (const auto& planet : world.planets)
        {
            planet.Draw(shader);
        }

        for (const auto& lightParticle : world.lightParticles)
        {
            pointRenderer.DrawTrail(
                particleShader,
                lightParticle.trail,
                lightParticle.trailLifetimeSeconds,
                lightParticle.pointSize,
                lightParticle.color
            );

            pointRenderer.DrawParticle(
                particleShader,
                lightParticle.transform.position,
                lightParticle.pointSize,
                lightParticle.color
            );
        }

        window.swapBuffers();
    }
    return 0;
}
