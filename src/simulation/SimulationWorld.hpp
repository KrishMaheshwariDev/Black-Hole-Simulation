#pragma once

#include <list>

#include "BlackHole.hpp"
#include "LightParticle.hpp"
#include "Planet.hpp"

struct SimulationWorld
{
    std::list<Planet> planets;
    std::list<BlackHole> blackHoles;
    std::list<LightParticle> lightParticles;
};
