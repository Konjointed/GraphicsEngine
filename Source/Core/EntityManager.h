#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <typeindex>

#include "Systems/ISystem.h"
#include "Systems/IRenderSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/CameraSystem.h"
#include "Components/Components.h"

#include "Entity.h"

// According to ChatGPT: "Ensures that entities can quickly and uniquely identified when uses as keys in has-based containers"
namespace std {
	template <>
	struct hash<Entity> {
		size_t operator()(const Entity& entity) const {
			return hash<unsigned>()(entity.id);
		}
	};
}

class EntityManager {
public:
	template <typename SystemType, typename... Args>
	void registerSystem(Args&&... args) {
		SystemType* system = new SystemType(std::forward<Args>(args)...);
		systems.push_back(system);
	}

	template <typename RenderSystemType, typename... Args>
	void registerRenderSystem(RenderStage stage, Args&&... args) {
		RenderSystemType* renderSystem = new RenderSystemType(std::forward<Args>(args)...);
		renderSystems[stage].push_back(renderSystem);
	}

	template <typename T>
	bool hasComponent(Entity entity) {
		auto it = components.find(entity);
		if (it != components.end()) {
			return it->second.find(typeid(T)) != it->second.end();
		}
		return false;
	}

	template <typename T>
	void addComponent(Entity entity, T* component) {
		components[entity][typeid(T)] = component;
	}

	template <typename T>
	T& getComponent(Entity entity) {
		return *static_cast<T*>(components[entity][typeid(T)]);
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
	void render(RenderStage stage);

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
	std::map<RenderStage, std::vector<IRenderSystem*>> renderSystems;
	std::unordered_set<Entity> entities;
	std::unordered_map<Entity, std::unordered_map<std::type_index, Component*>> components;
};