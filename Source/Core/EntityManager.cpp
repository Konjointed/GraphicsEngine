#include "EntityManager.h"

#include <iostream>

void EntityManager::update(float timestep) {
	for (auto& system : systems) {
		system->update(*this, timestep);
	}
}

void EntityManager::render(RenderStage stage)
{
    auto systems = renderSystems.find(stage);

    if (systems != renderSystems.end()) {
        for (IRenderSystem* system : systems->second) {
            system->render(*this);
        }
    }
}

Entity EntityManager::createEntity(const std::string& name) {
	Entity entity{ nextEntityId++ };
	entities.insert(entity);

	addComponent<TagComponent>(entity, new TagComponent(name));
	addComponent<TransformComponent>(entity, new TransformComponent());

	return entity;
}

void EntityManager::destroyEntity(Entity entity) {
    // Erase the entity from the main set
    entities.erase(entity);

    // Find the entity's component map
    auto compMapIt = components.find(entity);
    if (compMapIt != components.end()) {
        // Iterate over each component and delete it
        for (auto& [typeIndex, compPtr] : compMapIt->second) {
            delete compPtr; // only if you're using raw pointers
        }

        // Erase the component map for this entity
        components.erase(compMapIt);
    }
}

bool EntityManager::alive(Entity entity) {
	return entities.find(entity) != entities.end();
}
