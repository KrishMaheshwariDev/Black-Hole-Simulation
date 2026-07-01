#include "PhysicsSystem.hpp"

namespace
{
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

    void UpdateLightParticleTrails(SimulationWorld& world, float deltaTime)
    {
        for (auto& lightParticle : world.lightParticles)
        {
            lightParticle.UpdateTrail(deltaTime);
            lightParticle.RecordTrailPoint();
        }
    }
}

PhysicsSystem::PhysicsSystem()
{
    AddStep(IntegrateBodies);
    AddStep(UpdateLightParticleTrails);
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
