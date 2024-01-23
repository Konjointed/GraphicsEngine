#pragma once

class EntityManager;

enum RenderStage {
	GEOMETRY_PASS
};

class IRenderSystem {
public:
	virtual void render(EntityManager& entityManager) = 0;
	RenderStage stage;
};