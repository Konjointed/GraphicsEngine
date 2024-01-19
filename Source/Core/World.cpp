#include "World.h"

int createEntity(const std::string& name) {
	int entity = nextEntityId++;

	addComponent<TagComponent>(entity, TagComponent());
	addComponent<TransformComponent>(entity, TransformComponent());

	return entity;
}

void destroyEntity(int entity) {

}
