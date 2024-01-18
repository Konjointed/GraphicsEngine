#include "Camera.h"

#include <SDL.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"

void DebugCameraBehavior::Update(Camera& camera, float timestep, Input& input)
{
	float speed = 5.0f;
	float sensitivity = 0.1f;

	camera.fov = 70.0f;
	camera.aspectRatio = 16.0f / 9.0f;
	camera.nearPlane = 0.1f;
	camera.farPlane = 500.0f;

    if (input.IsMouseButtonDown(SDL_BUTTON_RIGHT)) {
        Pivot(camera, input.DeltaMouseX(), input.DeltaMouseY(), sensitivity);
    }

    UpdateDirectionVectors(camera);

    if (input.IsKeyDown(SDLK_w))
        Move(camera, camera.forward, speed, timestep);

    if (input.IsKeyDown(SDLK_s))
        Move(camera, -camera.forward, speed, timestep);

    if (input.IsKeyDown(SDLK_a))
        Move(camera, -glm::normalize(glm::cross(camera.forward, camera.up)), speed, timestep);

    if (input.IsKeyDown(SDLK_d))
        Move(camera, glm::normalize(glm::cross(camera.forward, camera.up)), speed, timestep);
}

void Move(Camera& camera, const glm::vec3& direction, float speed, float timestep) {
    camera.position += direction * speed * timestep;
}

void Pivot(Camera& camera, float mouseXChange, float mouseYChange, float sensitivity) {
    camera.yaw += mouseXChange * sensitivity;
    camera.pitch -= mouseYChange * sensitivity;
    camera.pitch = glm::clamp(camera.pitch, -89.0f, 89.0f);
}

void UpdateDirectionVectors(Camera& camera) {
    glm::vec3 forward;
    forward.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    forward.y = sin(glm::radians(camera.pitch));
    forward.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    camera.forward = glm::normalize(forward);

    camera.right = glm::normalize(glm::cross(camera.forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    camera.up = glm::normalize(glm::cross(camera.right, camera.forward));
}

glm::mat4 ComputeViewMatrix(const Camera& camera) {
	return glm::lookAt(camera.position, camera.position + camera.forward, camera.up);
}

glm::mat4 ComputeProjectionMatrix(const Camera& camera) {
	return glm::perspective(glm::radians(camera.fov), camera.aspectRatio, camera.nearPlane, camera.farPlane);
}