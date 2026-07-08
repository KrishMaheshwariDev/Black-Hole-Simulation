#pragma once

#include <cstddef>

#include <glm/vec4.hpp>

namespace Config
{
    namespace Simulation
    {
        inline constexpr float kFixedTicksPerSecond = 240.0f;
        inline constexpr float kTimeScale = 0.22f;

        inline constexpr double kPixelsPerDistanceUnit = 10.0;
        inline constexpr double kKilometersPerDistanceUnit = 100000.0;
        inline constexpr double kPixelsPerWorldUnit = 10.0;
        inline constexpr double kMetersPerKilometer = 1000.0;
        inline constexpr double kKilometersPerWorldUnit =
            kKilometersPerDistanceUnit * (kPixelsPerWorldUnit / kPixelsPerDistanceUnit);
        inline constexpr double kMetersPerWorldUnit =
            kKilometersPerWorldUnit * kMetersPerKilometer;

        inline constexpr double kGravitationalConstant = 6.67430e-11;
        inline constexpr double kSpeedOfLightMetersPerSecond = 299792458.0;
        inline constexpr double kMinimumGravityDistance = 1.0e-5;
        inline constexpr double kMaximumGravityAcceleration = 25.0;
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
        inline constexpr float kDefaultPointSize = 5.0f;
        inline constexpr float kDefaultMass = 1.0f;
        inline constexpr glm::vec4 kDefaultColor{1.0f, 0.95f, 0.7f, 1.0f};
        inline constexpr float kDefaultLifetimeSeconds = 6.0f;
        inline constexpr float kDefaultTrailLifetimeSeconds = 2.0f;
        inline constexpr std::size_t kDefaultMaxTrailPoints = 48;
        inline constexpr float kTrailPointSpacingWorldUnits = 0.015f;
    }
}
