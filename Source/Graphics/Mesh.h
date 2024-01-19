#pragma once

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

struct Resources;

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
	unsigned int vao, vbo, ebo;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
std::vector<Mesh> ProcessNode(aiNode* node, const aiScene* scene);
void LoadMesh(Resources& resources, const std::string& filepath, const std::string& name);