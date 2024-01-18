#pragma once

#include <memory>

#include <glm/glm.hpp>

class Input;
struct Camera;

struct CameraBehavior {
    virtual void Update(Camera& camera, float timestep, Input& input) = 0;
};

struct DebugCameraBehavior : public CameraBehavior {
	void Update(Camera& camera, float timestep, Input& input) override;
};

struct Camera {
	glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;

    float yaw;
    float pitch;
    float roll;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    std::unique_ptr<CameraBehavior> behavior;

    void Update(float timestep, Input& input) {
        if (behavior) {
            behavior->Update(*this, timestep, input);
        }
    }
};

void Move(Camera& camera, const glm::vec3& direction, float speed, float timestep);
void Pivot(Camera& camera, float mouseXChange, float mouseYChange, float sensitivity);
void UpdateDirectionVectors(Camera& camera);

glm::mat4 ComputeViewMatrix(const Camera& camera);
glm::mat4 ComputeProjectionMatrix(const Camera& camera);