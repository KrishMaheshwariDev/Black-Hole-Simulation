#include "GravityModule.hpp"

#include <algorithm>
#include <cmath>
#include <sstream>

#include <glm/geometric.hpp>

#include "Config.hpp"
#include "core/Logger.hpp"

namespace
{
    constexpr double kMetersPerWorldUnit = Config::Simulation::kMetersPerWorldUnit;
    constexpr double kGravityConstant = Config::Simulation::kGravitationalConstant;
    constexpr double kMinimumDistance = Config::Simulation::kMinimumGravityDistance;
    constexpr double kMaximumAcceleration = Config::Simulation::kMaximumGravityAcceleration;
    constexpr const char* kLogSource = "GravityModule";

    double ResolveSafeDistance()
    {
        return kMinimumDistance;
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
        const double distanceSquared = glm::dot(offset, offset);

        if (!std::isfinite(distanceSquared))
        {
            Core::Logger::Error(kLogSource, "Skipped gravity due to non-finite body distance");
            return;
        }

        const double safeDistance = ResolveSafeDistance();
        const double clampedDistanceSquared = std::max(distanceSquared, safeDistance * safeDistance);

        if (distanceSquared <= kMinimumDistance * kMinimumDistance)
        {
            Core::Logger::Warn(kLogSource, "Body reached the black hole singularity clamp radius");
        }

        const double distance = std::sqrt(clampedDistanceSquared);
        const glm::vec2 direction =
            distance > 0.0
                ? offset / static_cast<float>(distance)
                : glm::vec2{0.0f, 0.0f};
        const double distanceInMeters = distance * kMetersPerWorldUnit;
        const double accelerationInMetersPerSecondSquared =
            kGravityConstant *
            blackHole.physics.mass /
            (distanceInMeters * distanceInMeters);
        const double accelerationInWorldUnitsPerSecondSquared =
            accelerationInMetersPerSecondSquared / kMetersPerWorldUnit;
        const double forceMagnitude =
            accelerationInWorldUnitsPerSecondSquared * targetPhysics.mass;

        glm::vec2 gravityForce = direction * static_cast<float>(forceMagnitude);

        if (!std::isfinite(gravityForce.x) || !std::isfinite(gravityForce.y))
        {
            std::ostringstream message;
            message
                << "Computed non-finite gravity force at distanceSquared="
                << clampedDistanceSquared;
            Core::Logger::Error(kLogSource, message.str());
            return;
        }

        const double accelerationMagnitude = glm::length(gravityForce) / targetPhysics.mass;
        if (accelerationMagnitude > kMaximumAcceleration)
        {
            gravityForce *= static_cast<float>(kMaximumAcceleration / accelerationMagnitude);
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
