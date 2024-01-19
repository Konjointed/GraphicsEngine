#pragma once

#include "Renderer.h"
#include "Scene.h"

class Simulation {
public:
	Simulation() = default;
	void Update(float timestep);
};