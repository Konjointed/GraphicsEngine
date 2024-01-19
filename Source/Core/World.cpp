#include "World.h"

#include <iostream>

void ECS::update(float timestep) {
	for (auto& system : systems) {
		system->update(*this, timestep);
	}
}

Entity ECS::createEntity(const std::string& name) {
	Entity entity{ nextEntityId++ };
	entities.insert(entity);

	addComponent<TagComponent>(entity, TagComponent(name));
	addComponent<TransformComponent>(entity, TransformComponent());

	return entity;
}

void ECS::destroyEntity(Entity entity) {
	entities.erase(entity);

	tagComponents.erase(entity);
	transformComponents.erase(entity);
	meshComponents.erase(entity);
}

bool ECS::alive(Entity entity) {
	return entities.find(entity) != entities.end();
}
