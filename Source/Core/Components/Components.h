// TODO: Make the CameraComponent store a Camera object
// ScriptComponent stores a path to the script

#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Component {
    virtual ~Component() = default;

    int entity;
};

struct TagComponent : Component {
    std::string tag;

    TagComponent() = default;
    TagComponent(const std::string& tag) : tag(tag) {}
};

struct TransformComponent : Component {
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;

    //TransformComponent() = default;
    TransformComponent(const glm::vec3& translation = glm::vec3(0.0f),
        const glm::vec3& rotation = glm::vec3(0.0f),
        const glm::vec3& scale = glm::vec3(1.0f))
        : translation(translation), rotation(rotation), scale(scale) {}
};

struct MeshComponent : Component {
    std::string meshName;

    MeshComponent() = default;
    MeshComponent(const std::string& meshName) : meshName(meshName) {}
};

struct CameraComponent : Component {
    float speed = 5.0f;
    float sensitivity = 0.1f;

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

    CameraComponent() : forward(glm::vec3(0.0f, 0.0f, -1.0f)), right(glm::vec3(1.0f, 0.0f, 0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
		yaw(0.0f), pitch(0.0f), roll(0.0f), fov(45.0f), aspectRatio(1.0f), nearPlane(0.1f), farPlane(500.0f) {}
};