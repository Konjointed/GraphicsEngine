#include "RenderSystem.h"

#include <iostream>

#include <glad/glad.h>

#include "../Game.h"
#include "../EntityManager.h"

void RenderSystem::render(EntityManager& entityManager) {
	for (auto& entity : entityManager.queryEntitiesWith<MeshComponent, TransformComponent>()) {
		MeshComponent& mesh = entityManager.getComponent<MeshComponent>(entity);
		TransformComponent& transform = entityManager.getComponent<TransformComponent>(entity);

		Resources& resources = Game::Instance().getResources();
		Mesh actualMesh = resources.meshes[mesh.meshName];

		glBindVertexArray(actualMesh.vao);
		glDrawElements(GL_TRIANGLES, actualMesh.indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}