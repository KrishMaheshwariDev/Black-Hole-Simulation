#pragma once

#include <cstddef>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "SimulationWorld.hpp"

struct BlackHoleSpawn
{
    float radius{0.22f};
    unsigned int segments{64};
    Transform transform{};
    PhysicsBody physics{};
    float eventHorizonRadius{0.22f};
};

struct PlanetSpawn
{
    float radius{0.08f};
    unsigned int segments{64};
    Transform transform{};
    PhysicsBody physics{};
    float collisionRadius{0.08f};
};

struct LightParticleSpawn
{
    float pointSize{5.0f};
    Transform transform{};
    PhysicsBody physics{};
    glm::vec4 color{1.0f, 0.95f, 0.7f, 1.0f};
    float collisionRadius{0.0f};
};

struct LightParticleStreamSpawn
{
    std::size_t count{1};
    glm::vec2 startPosition{0.0f, 0.0f};
    glm::vec2 separation{0.0f, 0.0f};
    float pointSize{5.0f};
    PhysicsBody physics{};
    glm::vec4 color{1.0f, 0.95f, 0.7f, 1.0f};
    float collisionRadius{0.0f};
};

class InitialStateBuilder
{
public:
    explicit InitialStateBuilder(SimulationWorld& world);

    InitialStateBuilder& AddBlackHole(const BlackHoleSpawn& spawn);
    InitialStateBuilder& AddPlanet(const PlanetSpawn& spawn);
    InitialStateBuilder& AddLightParticle(const LightParticleSpawn& spawn);
    InitialStateBuilder& AddLightParticleStream(const LightParticleStreamSpawn& spawn);

private:
    SimulationWorld& m_World;
};
