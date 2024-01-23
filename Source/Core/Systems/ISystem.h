#pragma once

class EntityManager;

// TODO: Init and Shutdown methods?
class ISystem {
public:
	virtual void update(EntityManager& entityManager, float timestep) = 0;
};