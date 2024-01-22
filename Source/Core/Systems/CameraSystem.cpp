#include "CameraSystem.h"

#include <SDL.h>

#include <iostream>

#include "../EntityManager.h"
#include "../Input.h"
#include "../Game.h"

void CameraSystem::update(EntityManager& entityManager, float timestep)
{
	for (auto& entity : entityManager.queryEntitiesWith<CameraComponent, TransformComponent>()) {
		CameraComponent& camera = entityManager.getComponent<CameraComponent>(entity);
		TransformComponent& transform = entityManager.getComponent<TransformComponent>(entity);

		Input& input = Game::Instance().getInput();

		// Pivot Camera
		if (input.IsMouseButtonDown(SDL_BUTTON_RIGHT)) {
			float deltaMouseX = input.DeltaMouseX();
			float deltaMouseY = input.DeltaMouseY();

			camera.yaw += deltaMouseX * camera.sensitivity;
			camera.pitch -= deltaMouseY * camera.sensitivity;
			camera.pitch = glm::clamp(camera.pitch, -89.0f, 89.0f);
		}

		// Update Vectors
		camera.forward.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
		camera.forward.y = sin(glm::radians(camera.pitch));
		camera.forward.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
		camera.forward = glm::normalize(camera.forward);
		camera.right = glm::normalize(glm::cross(camera.forward, glm::vec3(0.0f, 1.0f, 0.0f)));
		camera.up = glm::normalize(glm::cross(camera.right, camera.forward));

		// Move Camera
		if (input.IsKeyDown(SDLK_w)) {
			transform.translation += camera.forward * camera.speed * timestep;
		}

		if (input.IsKeyDown(SDLK_s)) {
			transform.translation -= camera.forward * camera.speed * timestep;
		}

		if (input.IsKeyDown(SDLK_a)) {
			transform.translation -= camera.right * camera.speed * timestep;
		}

		if (input.IsKeyDown(SDLK_d)) {
			transform.translation += camera.right * camera.speed * timestep;
		}
	}
}
