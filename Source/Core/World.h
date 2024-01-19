#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "ISystem.h"
#include "Components.h"
#include "Entity.h"

#include "RenderSystem.h"

// According to ChatGPT: "Ensures that entities can quickly and uniquely identified when uses as keys in has-based containers"
namespace std {
	template <>
	struct hash<Entity> {
		size_t operator()(const Entity& entity) const {
			return hash<unsigned>()(entity.id);
		}
	};
}

class ECS {
public:
	template <typename SystemType, typename... Args>
	void registerSystem(Args&&... args) {
		SystemType* system = new SystemType(std::forward<Args>(args)...);
		systems.push_back(system);
	}

	template <typename T>
	bool hasComponent(Entity entity) {
		if constexpr (std::is_same<T, TagComponent>::value) {
			return tagComponents.find(entity) != tagComponents.end();
		}
		else if constexpr (std::is_same<T, TransformComponent>::value) {
			return transformComponents.find(entity) != transformComponents.end();
		}
		else if constexpr (std::is_same<T, MeshComponent>::value) {
			return meshComponents.find(entity) != meshComponents.end();
		}

		return false;
	}

	template <typename T>
	void addComponent(Entity entity, T component) {
		if constexpr (std::is_same<T, TagComponent>::value) {
			tagComponents[entity] = component;
		}
		else if constexpr (std::is_same<T, TransformComponent>::value) {
			transformComponents[entity] = component;
		}
		else if constexpr (std::is_same<T, MeshComponent>::value) {
			meshComponents[entity] = component;
		}
	}

	template <typename T>
	T& getComponent(Entity entity) {
		if constexpr (std::is_same<T, TagComponent>::value) {
			return tagComponents.at(entity);
		}
		else if constexpr (std::is_same<T, TransformComponent>::value) {
			return transformComponents.at(entity);
		}
		else if constexpr (std::is_same<T, MeshComponent>::value) {
			return meshComponents.at(entity);
		}
		//else {
		//	static_assert(dependent_false_v<T>, "Component type not recognized");
		//}
	}

	template <typename... ComponentTypes>
	std::vector<Entity> queryEntitiesWith() {
		std::vector<Entity> matchingEntities;

		for (const auto& entity : entities) {
			if ((hasComponent<ComponentTypes>(entity) && ...)) {
				matchingEntities.push_back(entity);
			}
		}

		return matchingEntities;
	}

	void update(float timestep);

	Entity createEntity(const std::string& name);
	void destroyEntity(Entity entity);
	bool alive(Entity entity);
private:
	template <typename... ComponentTypes>
	bool hasComponents(Entity entity) {
		return (hasComponent<ComponentTypes>(entity) && ...);
	}
private:
	int nextEntityId = 0;

	std::vector<ISystem*> systems;
	std::unordered_set<Entity> entities;
	std::unordered_map<Entity, TagComponent> tagComponents;
	std::unordered_map<Entity, TransformComponent> transformComponents;
	std::unordered_map<Entity, MeshComponent> meshComponents;
};