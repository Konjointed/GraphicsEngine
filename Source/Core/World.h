#pragma once

#include <vector>

#include "Components.h"

struct {
	std::vector<TagComponent> tags;
	std::vector<TransformComponent> transforms;
	std::vector<MeshComponent> meshes;
} g_components;

int nextEntityId = 0;

template <typename T>
void addComponent(int entity, T component) {
	if (entity < 0 || entity >= g_components.tags.size()) {
		throw std::runtime_error("Invalid entity ID");
	}

	if (hasComponent<T>(entity)) {
		throw std::runtime_error("Entity already has a component of the specified type");
	}

	if (std::is_same<T, TagComponent>::value) {
		g_components.tags.push_back(component);
	}
	else if (std::is_same<T, TransformComponent>::value) {
		g_components.transforms.push_back(component);
	}
	else if (std::is_same<T, MeshComponent>::value) {
		g_components.meshes.push_back(component);
	}
	else {
		throw std::runtime_error("Unsupported component type");
	}
}

template <typename T>
bool hasComponent(int entity) {
	if (entity < 0 || entity >= g_components.tags.size()) {
		throw std::runtime_error("Invalid entity ID");
	}

	if (std::is_same<T, TagComponent>::value) {
		return g_components.tags[entity] == entity;
	}
	else if (std::is_same<T, TransformComponent>::value) {
		return g_components.transforms[entity] == entity;
	}
	else if (std::is_same<T, MeshComponent>::value) {
		return g_components.meshes[entity] == entity;
	}
	else {
		throw std::runtime_error("Invalid component type");
	}
}

template <typename... ComponentTypes>
std::vector<int> queryEntitiesWith() {
	std::vector<int> matchingEntities;

	// Iterate through all entities
	for (int entity = 0; entity < g_components.tags.size(); entity++) {
		// Check if the entity has all required components
		if (hasAllComponents<ComponentTypes...>(entity)) {
			matchingEntities.push_back(entity);
		}
	}

	return matchingEntities;
}

template <typename... ComponentTypes>
bool hasAllComponents(int entity) {
	return (hasComponent<ComponentTypes>(entity) && ...);
}

int createEntity(const std::string& name);
void destroyEntity(int entity);