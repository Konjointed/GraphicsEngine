#pragma once

struct Scene;

class Simulation {
public:
	Simulation(Scene& scene);
	void Update(float timestep);
};