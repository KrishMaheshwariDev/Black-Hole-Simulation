#pragma once

#include <cstddef>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace Config
{
    namespace Simulation
    {
        inline constexpr float kFixedTicksPerSecond = 20.0f;

        inline constexpr float kPixelsPerDistanceUnit = 100.0f;
        inline constexpr float kKilometersPerDistanceUnit = 100000.0f;
        inline constexpr float kPixelsPerWorldUnit = 100.0f;

        inline constexpr float kGravityConstant = 8000000.0f;
        inline constexpr float kMinimumGravityDistance = 0.001f;
        inline constexpr float kMaximumGravityAcceleration = 1.5f;
    }

    namespace Camera
    {
        inline constexpr float kDefaultZoom = 1.0f;
        inline constexpr float kMinimumZoom = 0.25f;
        inline constexpr float kMaximumZoom = 4.0f;
        inline constexpr float kZoomMultiplierPerStep = 1.15f;
    }

    namespace Particles
    {
        inline constexpr float kDefaultLifetimeSeconds = 5.0f;
        inline constexpr float kDefaultTrailLifetimeSeconds = 1.0f;
        inline constexpr std::size_t kDefaultMaxTrailPoints = 24;
    }

    namespace Scene
    {
        inline constexpr float kBlackHoleRadius = 0.22f;
        inline constexpr unsigned int kBlackHoleSegments = 64;
        inline constexpr glm::vec2 kBlackHolePosition{0.0f, 0.0f};
        inline constexpr float kBlackHoleMass = 1000.0f;
        inline constexpr float kBlackHoleEventHorizonRadius = 0.22f;

        inline constexpr float kPlanetRadius = 0.08f;
        inline constexpr unsigned int kPlanetSegments = 64;
        inline constexpr glm::vec2 kPlanetPosition{-0.7f, 0.2f};
        inline constexpr float kPlanetMass = 10.0f;

        inline constexpr float kLightParticlePointSize = 5.0f;
        inline constexpr glm::vec2 kLightParticlePosition{-0.25f, -0.45f};
        inline constexpr float kLightParticleMass = 0.1f;
        inline constexpr glm::vec4 kLightParticleColor{1.0f, 0.95f, 0.7f, 1.0f};
    }
}
