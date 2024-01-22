#pragma once

class EntityManager;

enum RenderStage {
	RENDER_STAGE_DEFERRED_GEOMETRY_PASS,
	RENDER_STAGE_DIRECTIONAL_LIGHTING,
};

// TODO: Init and Shutdown methods?
class ISystem {
public:
	virtual void update(EntityManager& entityManager, float timestep) = 0;
};

class IRenderSystem {
public:
	virtual void render() = 0;
	RenderStage getRenderStage() const { return stage; }
private:
	RenderStage stage;
};