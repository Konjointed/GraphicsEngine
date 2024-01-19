#pragma once

#include "ISystem.h"

#include <iostream>

#include "World.h"

class RenderSystem : public ISystem {
public:
	void update(float timestep) override {
		for (int entity : queryEntitiesWith<MeshComponent, TransformComponent>()) {
			std::cout << "RenderSystem: " << entity << std::endl;
		}
	}
};
