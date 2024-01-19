#pragma once

class ECS;
struct Scene;

class Simulation {
public:
	Simulation(Scene& scene, ECS& ecs);
	void Update(float timestep);
};