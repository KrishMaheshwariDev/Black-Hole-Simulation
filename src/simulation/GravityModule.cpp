#include "GravityModule.hpp"

#include <algorithm>
#include <cmath>
#include <sstream>

#include <glm/geometric.hpp>

#include "Config.hpp"
#include "core/Logger.hpp"

namespace
{
    constexpr float kPixelsPerDistanceUnit = Config::Simulation::kPixelsPerDistanceUnit;
    constexpr float kKilometersPerDistanceUnit = Config::Simulation::kKilometersPerDistanceUnit;
    constexpr float kKilometersPerPixel =
        kKilometersPerDistanceUnit / kPixelsPerDistanceUnit;
    constexpr float kPixelsPerWorldUnit = Config::Simulation::kPixelsPerWorldUnit;
    constexpr float kKilometersPerWorldUnit =
        kKilometersPerPixel * kPixelsPerWorldUnit;
    constexpr float kGravityConstant = Config::Simulation::kGravityConstant;
    constexpr float kMinimumDistance = Config::Simulation::kMinimumGravityDistance;
    constexpr float kMaximumAcceleration = Config::Simulation::kMaximumGravityAcceleration;
    constexpr const char* kLogSource = "GravityModule";

    float ResolveSafeDistance(float eventHorizonRadius)
    {
        return std::max(eventHorizonRadius, kMinimumDistance);
    }

    void ApplyBlackHoleGravity(
        Transform& targetTransform,
        PhysicsBody& targetPhysics,
        const BlackHole& blackHole
    )
    {
        if (targetPhysics.isStatic)
        {
            return;
        }

        if (targetPhysics.mass <= 0.0f)
        {
            Core::Logger::Error(kLogSource, "Skipped gravity on body with non-positive mass");
            return;
        }

        if (blackHole.physics.mass <= 0.0f)
        {
            Core::Logger::Error(kLogSource, "Skipped black hole with non-positive mass");
            return;
        }

        const glm::vec2 offset = blackHole.transform.position - targetTransform.position;
        const float distanceSquared = glm::dot(offset, offset);

        if (!std::isfinite(distanceSquared))
        {
            Core::Logger::Error(kLogSource, "Skipped gravity due to non-finite body distance");
            return;
        }

        const float safeDistance = ResolveSafeDistance(blackHole.eventHorizonRadius);
        const float clampedDistanceSquared = std::max(distanceSquared, safeDistance * safeDistance);

        if (distanceSquared <= kMinimumDistance * kMinimumDistance)
        {
            Core::Logger::Warn(kLogSource, "Body reached the black hole singularity clamp radius");
        }

        const float distance = std::sqrt(clampedDistanceSquared);
        const glm::vec2 direction = distance > 0.0f ? offset / distance : glm::vec2{0.0f, 0.0f};
        const float distanceInKilometers = distance * kKilometersPerWorldUnit;
        const float distanceSquaredInKilometers =
            distanceInKilometers * distanceInKilometers;
        const float forceMagnitude =
            kGravityConstant *
            targetPhysics.mass *
            blackHole.physics.mass /
            distanceSquaredInKilometers;

        glm::vec2 gravityForce = direction * forceMagnitude;

        if (!std::isfinite(gravityForce.x) || !std::isfinite(gravityForce.y))
        {
            std::ostringstream message;
            message
                << "Computed non-finite gravity force at distanceSquared="
                << clampedDistanceSquared;
            Core::Logger::Error(kLogSource, message.str());
            return;
        }

        const float accelerationMagnitude = glm::length(gravityForce) / targetPhysics.mass;
        if (accelerationMagnitude > kMaximumAcceleration)
        {
            gravityForce *= kMaximumAcceleration / accelerationMagnitude;
            Core::Logger::Warn(kLogSource, "Clamped gravity acceleration to keep free-fall stable");
        }

        targetPhysics.AddForce(gravityForce);
    }
}

void GravityModule::Apply(SimulationWorld& world, float deltaTime) const
{
    if (!(deltaTime > 0.0f) || !std::isfinite(deltaTime))
    {
        Core::Logger::Error(kLogSource, "Skipped gravity step due to invalid delta time");
        return;
    }

    for (auto& planet : world.planets)
    {
        for (const auto& blackHole : world.blackHoles)
        {
            ApplyBlackHoleGravity(planet.transform, planet.physics, blackHole);
        }
    }

    for (auto& lightParticle : world.lightParticles)
    {
        for (const auto& blackHole : world.blackHoles)
        {
            ApplyBlackHoleGravity(lightParticle.transform, lightParticle.physics, blackHole);
        }
    }

    for (auto& blackHole : world.blackHoles)
    {
        for (const auto& sourceBlackHole : world.blackHoles)
        {
            if (&blackHole == &sourceBlackHole)
            {
                continue;
            }

            ApplyBlackHoleGravity(blackHole.transform, blackHole.physics, sourceBlackHole);
        }
    }
}
