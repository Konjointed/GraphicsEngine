#include "Simulation.h"
#include "Game.h"
#include "World.h"

Simulation::Simulation(Scene& scene)
{
	scene.shaderProgram.AddShaders(GL_VERTEX_SHADER, "Resources/Shaders/Default.vert", GL_FRAGMENT_SHADER, "Resources/Shaders/Default.frag");
	scene.shaderProgram.Link();

	int entity = createEntity("Suzanne");
	addComponent<MeshComponent>(entity, MeshComponent());
}

void Simulation::Update(float timestep)
{
}
