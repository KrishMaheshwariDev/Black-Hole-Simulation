// #include <vector>
// #include <cmath>
// #include <cstdint>
#include <windows.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <SOGL/window/Window.hpp>
#include <SOGL/graphic/Renderer.hpp>
#include <SOGL/shaders/Shader.hpp>

#include "Config.hpp"
#include "core/Camera2D.hpp"
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

int main() {
    // Initialize the window
    Core::Logger::Info("Main", "Starting Black Hole Simulation");

    Window window(1280, 720, "SOGL Example");
    Shader shader("../assets/shaders/basic.vert", "../assets/shaders/basic.frag");
    Shader particleShader("../assets/shaders/particle.vert", "../assets/shaders/particle.frag");
    PointRenderer pointRenderer;
    FixedTimestep fixedTimestep(Config::Simulation::kFixedTicksPerSecond);
    PhysicsSystem physicsSystem;
    Camera2D camera;
    SimulationWorld world;

    world.blackHoles.emplace_back(
        Config::Scene::kBlackHoleRadius,
        Config::Scene::kBlackHoleSegments,
        Transform{
            .position = Config::Scene::kBlackHolePosition,
            .rotation = 0.0f,
            .scale = {1.0f, 1.0f}
        },
        PhysicsBody{
            .mass = Config::Scene::kBlackHoleMass,
            .velocity = {0.0f, 0.0f},
            .accumulatedForce = {0.0f, 0.0f},
            .isStatic = true
        },
        Config::Scene::kBlackHoleEventHorizonRadius
    );

    world.planets.emplace_back(
        Config::Scene::kPlanetRadius,
        Config::Scene::kPlanetSegments,
        Transform{
            .position = Config::Scene::kPlanetPosition,
            .rotation = 0.0f,
            .scale = {1.0f, 1.0f}
        },
        PhysicsBody{
            .mass = Config::Scene::kPlanetMass,
            .velocity = {0.5f, .25f}
        }
    );

    world.lightParticles.emplace_back(
        Config::Scene::kLightParticlePointSize,
        Transform{
            .position = Config::Scene::kLightParticlePosition,
            .rotation = 0.0f,
            .scale = {1.0f, 1.0f}
        },
        PhysicsBody{
            .mass = Config::Scene::kLightParticleMass,
            .velocity = {0.5f, 0.5f}
        },
        Config::Scene::kLightParticleColor
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
        window.processInput();
        camera.UpdateFromInput(window.getNativeWindow());

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
            camera.CreateProjection(width, height);

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
