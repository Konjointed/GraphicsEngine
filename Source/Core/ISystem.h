#pragma once

class ECS;

// TODO: Init and Shutdown methods?
class ISystem {
public:
	virtual void update(ECS& ecs, float timestep) = 0;
};