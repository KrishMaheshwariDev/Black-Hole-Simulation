#pragma once

#include <functional>
#include <vector>

#include "SimulationWorld.hpp"

class PhysicsSystem
{
public:
    using PhysicsStep = std::function<void(SimulationWorld&, float)>;

    PhysicsSystem();

    void AddStep(PhysicsStep step);

    void Update(SimulationWorld& world, float deltaTime) const;

private:
    std::vector<PhysicsStep> m_Steps;
};
