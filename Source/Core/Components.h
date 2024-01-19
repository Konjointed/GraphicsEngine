#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/Mesh.h"

struct TagComponent {
    int entity;
    std::string tag;

    TagComponent() = default;
    TagComponent(const std::string& tag) : tag(tag) {}
};

struct TransformComponent {
    int entity;
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;

    //TransformComponent() = default;
    TransformComponent(const glm::vec3& translation = glm::vec3(0.0f),
        const glm::vec3& rotation = glm::vec3(0.0f),
        const glm::vec3& scale = glm::vec3(1.0f))
        : translation(translation), rotation(rotation), scale(scale) {}
};

struct MeshComponent {
    int entity;
    std::string meshName;

    MeshComponent() = default;
    MeshComponent(const std::string& meshName) : meshName(meshName) {}
};