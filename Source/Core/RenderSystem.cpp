#include "RenderSystem.h"
#include "World.h"
#include "Renderer.h"

void RenderSystem::update(ECS& ecs, float timestep) {
	for (auto& entity : ecs.queryEntitiesWith<MeshComponent, TransformComponent>()) {
		MeshComponent& mesh = ecs.getComponent<MeshComponent>(entity);
		TransformComponent& transform = ecs.getComponent<TransformComponent>(entity);

		renderer.SubmitMesh(mesh);
	}
}