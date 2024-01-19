#pragma once

#include "ISystem.h"

#include <iostream>

class ECS;
class Renderer;

class RenderSystem : public ISystem {
public:
	RenderSystem(Renderer& renderer) : renderer(renderer) {}
	void update(ECS& ecs, float timestep) override;
private:
	Renderer& renderer;
};
