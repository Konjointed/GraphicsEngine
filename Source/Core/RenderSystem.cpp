#include "RenderSystem.h"
#include "EntityManager.h"
#include "Renderer.h"

void RenderSystem::update(EntityManager& entityManager, float timestep) {
	for (auto& entity : entityManager.queryEntitiesWith<MeshComponent, TransformComponent>()) {
		MeshComponent& mesh = entityManager.getComponent<MeshComponent>(entity);
		TransformComponent& transform = entityManager.getComponent<TransformComponent>(entity);

		renderer.SubmitMesh(mesh);
	}
}