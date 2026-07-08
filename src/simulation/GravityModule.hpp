#pragma once

#include "SimulationWorld.hpp"

class GravityModule
{
public:
    void Apply(SimulationWorld& world, float deltaTime) const;
};
