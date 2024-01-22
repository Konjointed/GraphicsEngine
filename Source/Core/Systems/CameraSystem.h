#pragma once

#include "ISystem.h"

#include <iostream>

class EntityManager;
class Renderer;

class CameraSystem : public ISystem {
public:
	void update(EntityManager& entityManager, float timestep) override;
private:
};
