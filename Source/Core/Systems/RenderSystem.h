#pragma once

#include "IRenderSystem.h"

class EntityManager;

class RenderSystem : public IRenderSystem {
public:
	void render(EntityManager& entityManager) override;
};
