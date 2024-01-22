#pragma once

#include "ISystem.h"

#include <iostream>

class EntityManager;
class Renderer;

class RenderSystem : public ISystem {
public:
	RenderSystem(Renderer& renderer) : renderer(renderer) {}
	void update(EntityManager& entityManager, float timestep) override;
private:
	Renderer& renderer;
};
