#pragma once

class EntityManager;
struct Scene;

class Simulation {
public:
	Simulation(Scene& scene, EntityManager& entityManager);
	void Update(float timestep);
};