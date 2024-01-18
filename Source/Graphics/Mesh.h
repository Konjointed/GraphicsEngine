#pragma once

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

class Scene;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 color;
	// https://learnopengl.com/Advanced-Lighting/Normal-Mapping
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int vao, vbo, ebo;
};

Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
void ProcessNode(aiNode* node, const aiScene* scene, Scene& t_scene);