#include "PhysicsSystem.hpp"

#include <glm/geometric.hpp>

#include "GravityModule.hpp"

namespace
{
    GravityModule& GetGravityModule()
    {
        static GravityModule gravityModule;
        return gravityModule;
    }

    void ApplyGravity(SimulationWorld& world, float deltaTime)
    {
        GetGravityModule().Apply(world, deltaTime);
    }

    void AdvanceBody(Transform& transform, PhysicsBody& physics, float deltaTime)
    {
        if (physics.isStatic)
        {
            physics.ClearForces();
            return;
        }

        physics.velocity += physics.GetAcceleration() * deltaTime;
        transform.position += physics.velocity * deltaTime;
        physics.ClearForces();
    }

    void IntegrateBodies(SimulationWorld& world, float deltaTime)
    {
        for (auto& planet : world.planets)
        {
            AdvanceBody(planet.transform, planet.physics, deltaTime);
        }

        for (auto& blackHole : world.blackHoles)
        {
            AdvanceBody(blackHole.transform, blackHole.physics, deltaTime);
        }

        for (auto& lightParticle : world.lightParticles)
        {
            AdvanceBody(lightParticle.transform, lightParticle.physics, deltaTime);
        }
    }

    template <typename Body>
    bool IsInsideAnyBlackHole(const Body& body, const SimulationWorld& world)
    {
        for (const auto& blackHole : world.blackHoles)
        {
            const glm::vec2 offset = body.transform.position - blackHole.transform.position;
            const float collisionDistance = blackHole.eventHorizonRadius + body.collisionRadius;
            if (glm::dot(offset, offset) <= collisionDistance * collisionDistance)
            {
                return true;
            }
        }

        return false;
    }

    void ResolveBlackHoleCollisions(SimulationWorld& world, float)
    {
        world.planets.remove_if(
            [&world](const Planet& planet)
            {
                return IsInsideAnyBlackHole(planet, world);
            }
        );

        world.lightParticles.remove_if(
            [&world](const LightParticle& lightParticle)
            {
                return IsInsideAnyBlackHole(lightParticle, world);
            }
        );
    }

}

PhysicsSystem::PhysicsSystem()
{
    AddStep(ApplyGravity);
    AddStep(IntegrateBodies);
    AddStep(ResolveBlackHoleCollisions);
}

void PhysicsSystem::AddStep(PhysicsStep step)
{
    m_Steps.push_back(std::move(step));
}

void PhysicsSystem::Update(SimulationWorld& world, float deltaTime) const
{
    for (const auto& step : m_Steps)
    {
        step(world, deltaTime);
    }
}
