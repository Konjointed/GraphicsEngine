#include "Renderer.h"

#include <iostream>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Game.h"
#include "Components.h"

void Renderer::Draw(const Scene& scene, EntityManager& entityManager, const Resources& resources)
{
	Entity cameraEntity = scene.camera;
	CameraComponent& cameraComp = entityManager.getComponent<CameraComponent>(cameraEntity);
	TransformComponent& transformComp = entityManager.getComponent<TransformComponent>(cameraEntity);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(70.0f), 1280.0f / 720.0f, 0.1f, 500.0f);
	//glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 view = glm::lookAt(transformComp.translation, transformComp.translation + cameraComp.forward, cameraComp.up);

	ShaderProgram program = scene.shaderProgram;

	glUseProgram(program.ID());

	GLint location = program.UniformLocation("light.position");
	glUniform3f(location, 1.2f, 1.0f, 2.0f);

	location = program.UniformLocation("viewPos");
	glUniform3f(location, 0.0f, 0.0f, 3.0f);

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor.x = sin(SDL_GetTicks() / 1000.0f * 2.0f);
	lightColor.y = sin(SDL_GetTicks() / 1000.0f * 0.7f);
	lightColor.z = sin(SDL_GetTicks() / 1000.0f * 1.3f);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

	location = program.UniformLocation("light.ambient");
	glUniform3f(location, ambientColor.x, ambientColor.y, ambientColor.z);

	location = program.UniformLocation("light.diffuse");
	glUniform3f(location, diffuseColor.x, diffuseColor.y, diffuseColor.z);

	location = program.UniformLocation("light.specular");
	glUniform3f(location, 1.0f, 1.0f, 1.0f);

	location = program.UniformLocation("material.ambient");
	glUniform3f(location, 1.0f, 0.5f, 0.31f);

	location = program.UniformLocation("material.diffuse");
	glUniform3f(location, 1.0f, 0.5f, 0.31f);

	location = program.UniformLocation("material.specular");
	glUniform3f(location, 0.5f, 0.5f, 0.5f);

	location = program.UniformLocation("material.shininess");
	glUniform1f(location, 32.0f);

	location = program.UniformLocation("projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));

	location = program.UniformLocation("view");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));

	location = program.UniformLocation("model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const MeshComponent& mesh : meshes) {
		BindMesh(resources.meshes.at(mesh.meshName));
	}

	meshes.clear();
}

void Renderer::SubmitMesh(const MeshComponent& mesh)
{
	meshes.push_back(mesh);
}

void Renderer::BindMesh(const Mesh& mesh)
{
	glBindVertexArray(mesh.vao);
	glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
