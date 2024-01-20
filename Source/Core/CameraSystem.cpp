#include <SDL.h>

#include <iostream>

#include "CameraSystem.h"
#include "EntityManager.h"
#include "Input.h"

void CameraSystem::update(EntityManager& entityManager, float timestep)
{
	for (auto& entity : entityManager.queryEntitiesWith<CameraComponent, TransformComponent>()) {
		CameraComponent& camera = entityManager.getComponent<CameraComponent>(entity);
		TransformComponent& transform = entityManager.getComponent<TransformComponent>(entity);

		static float speed = 5.0f;

		if (entityManager.getInput().IsKeyDown(SDLK_w)) {
			transform.translation += camera.forward * speed * timestep;
		}

		if (entityManager.getInput().IsKeyDown(SDLK_s)) {
			transform.translation -= camera.forward * speed * timestep;
		}

		if (entityManager.getInput().IsKeyDown(SDLK_a)) {
			transform.translation -= camera.right * speed * timestep;
		}

		if (entityManager.getInput().IsKeyDown(SDLK_d)) {
			transform.translation += camera.right * speed * timestep;
		}
	}
}
