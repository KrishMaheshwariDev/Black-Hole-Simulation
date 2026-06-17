#pragma once

#include "SimulationComponents.hpp"

struct BlackHole
{
    Transform transform;

    float mass {1000.0f};

    float eventHorizonRadius {1.0f};
};