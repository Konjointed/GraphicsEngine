#include "Simulation.h"
#include "Game.h"
#include "EntityManager.h"

Simulation::Simulation(Scene& scene, EntityManager& entityManager)
{
	scene.shaderProgram.AddShaders(GL_VERTEX_SHADER, "Resources/Shaders/Default.vert", GL_FRAGMENT_SHADER, "Resources/Shaders/Default.frag");
	scene.shaderProgram.Link();

	Entity entity = entityManager.createEntity("Camera");
	entityManager.addComponent<CameraComponent>(entity, new CameraComponent());
	scene.camera = entity;

	entity = entityManager.createEntity("Suzanne");
	entityManager.addComponent<MeshComponent>(entity, new MeshComponent("suzanne"));
}

void Simulation::Update(float timestep)
{
}
