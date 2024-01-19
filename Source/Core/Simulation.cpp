#include "Simulation.h"
#include "Game.h"
#include "World.h"

Simulation::Simulation(Scene& scene, ECS& ecs)
{
	scene.shaderProgram.AddShaders(GL_VERTEX_SHADER, "Resources/Shaders/Default.vert", GL_FRAGMENT_SHADER, "Resources/Shaders/Default.frag");
	scene.shaderProgram.Link();

	Entity entity = ecs.createEntity("Suzanne");
	ecs.addComponent<MeshComponent>(entity, MeshComponent("cube"));
}

void Simulation::Update(float timestep)
{
}
