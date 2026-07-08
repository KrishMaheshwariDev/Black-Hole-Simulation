#include "InitialStateBuilder.hpp"

InitialStateBuilder::InitialStateBuilder(SimulationWorld& world)
    : m_World(world)
{
}

InitialStateBuilder& InitialStateBuilder::AddBlackHole(const BlackHoleSpawn& spawn)
{
    m_World.blackHoles.emplace_back(
        spawn.radius,
        spawn.segments,
        spawn.transform,
        spawn.physics,
        spawn.eventHorizonRadius
    );

    return *this;
}

InitialStateBuilder& InitialStateBuilder::AddPlanet(const PlanetSpawn& spawn)
{
    m_World.planets.emplace_back(
        spawn.radius,
        spawn.segments,
        spawn.transform,
        spawn.physics,
        spawn.collisionRadius
    );

    return *this;
}

InitialStateBuilder& InitialStateBuilder::AddLightParticle(const LightParticleSpawn& spawn)
{
    m_World.lightParticles.emplace_back(
        spawn.pointSize,
        spawn.transform,
        spawn.physics,
        spawn.color,
        spawn.collisionRadius
    );

    return *this;
}

InitialStateBuilder& InitialStateBuilder::AddLightParticleStream(
    const LightParticleStreamSpawn& spawn
)
{
    for (std::size_t index = 0; index < spawn.count; ++index)
    {
        AddLightParticle(
            LightParticleSpawn{
                .pointSize = spawn.pointSize,
                .transform = Transform{
                    .position = spawn.startPosition + (spawn.separation * static_cast<float>(index)),
                    .rotation = 0.0f,
                    .scale = {1.0f, 1.0f}
                },
                .physics = spawn.physics,
                .color = spawn.color,
                .collisionRadius = spawn.collisionRadius
            }
        );
    }

    return *this;
}
