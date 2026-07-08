// #include <vector>
// #include <cmath>
// #include <cstdint>
#include <windows.h>

#include <cmath>

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
#include "simulation/InitialStateBuilder.hpp"
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

namespace
{
    constexpr double kSolarMassKilograms = 1.98847e30;
    constexpr double kEarthMassKilograms = 5.9722e24;
    constexpr double kEarthRadiusMeters = 6.371e6;
    constexpr float kBlackHoleVisualRadiusWorldUnits = 0.18f;

    float MetersToWorldUnits(double meters)
    {
        return static_cast<float>(meters / Config::Simulation::kMetersPerWorldUnit);
    }

    float MetersPerSecondToWorldUnitsPerSecond(double metersPerSecond)
    {
        return static_cast<float>(metersPerSecond / Config::Simulation::kMetersPerWorldUnit);
    }

    glm::vec2 CreateTangentialVelocity(glm::vec2 position, double speedMetersPerSecond)
    {
        const float radius = glm::length(position);
        if (radius <= 0.0f)
        {
            return {0.0f, 0.0f};
        }

        const glm::vec2 tangent{
            -position.y / radius,
             position.x / radius
        };

        return tangent * MetersPerSecondToWorldUnitsPerSecond(speedMetersPerSecond);
    }

    SimulationWorld CreateInitialWorld()
    {
        const double blackHoleMassKilograms = 40000.0 * kSolarMassKilograms;

        const glm::vec2 planetPosition{-1.45f, 0.32f};
        const double planetOrbitalRadiusMeters =
            glm::length(planetPosition) * Config::Simulation::kMetersPerWorldUnit;
        const double planetCircularSpeedMetersPerSecond =
            std::sqrt(
                Config::Simulation::kGravitationalConstant *
                blackHoleMassKilograms /
                planetOrbitalRadiusMeters
            );

        SimulationWorld world;
        InitialStateBuilder initialState(world);

        initialState
            .AddBlackHole(
                BlackHoleSpawn{
                    .radius = kBlackHoleVisualRadiusWorldUnits,
                    .segments = 64,
                    .transform = Transform{
                        .position = {0.0f, 0.0f},
                        .rotation = 0.0f,
                        .scale = {1.0f, 1.0f}
                    },
                    .physics = PhysicsBody{
                        .mass = static_cast<float>(blackHoleMassKilograms),
                        .velocity = {0.0f, 0.0f},
                        .accumulatedForce = {0.0f, 0.0f},
                        .isStatic = true
                    },
                    .eventHorizonRadius = kBlackHoleVisualRadiusWorldUnits
                }
            )
            // .AddPlanet(
            //     PlanetSpawn{
            //         .radius = MetersToWorldUnits(kEarthRadiusMeters),
            //         .segments = 64,
            //         .transform = Transform{
            //             .position = planetPosition,
            //             .rotation = 0.0f,
            //             .scale = {1.0f, 1.0f}
            //         },
            //         .physics = PhysicsBody{
            //             .mass = static_cast<float>(kEarthMassKilograms),
            //             .velocity = {0.0, 0.0}
            //         }
            //     }
            // );
            .AddLightParticleStream(
                LightParticleStreamSpawn{
                    .count = 50,
                    .startPosition = {-1.9f, -0.95f},
                    .separation = {0.0f, 0.04f},
                    .pointSize = Config::Particles::kDefaultPointSize,
                    .physics = PhysicsBody{
                        .mass = Config::Particles::kDefaultMass,
                        .velocity = {
                            MetersPerSecondToWorldUnitsPerSecond(
                                Config::Simulation::kSpeedOfLightMetersPerSecond
                            ),
                            0.0f
                        }
                    },
                    .color = Config::Particles::kDefaultColor
                }
            );

        return world;
    }

    void UpdateLightParticleTrails(SimulationWorld& world, float frameDeltaTime)
    {
        for (auto& lightParticle : world.lightParticles)
        {
            lightParticle.UpdateTrail(frameDeltaTime);
            lightParticle.RecordTrailPointIfNeeded(
                Config::Particles::kTrailPointSpacingWorldUnits
            );
        }
    }
}

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
    SimulationWorld world = CreateInitialWorld();

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

        UpdateLightParticleTrails(
            world,
            fixedTimestep.GetLastFrameTime()
        );

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
