#pragma once

#include <string>
#include <vector>

#include "../Graphics/Mesh.h"
#include "../Graphics/ShaderProgram.h"
#include "Camera.h"

class Scene {
public:
	std::vector<Mesh> meshes;
	
	Camera camera;
	ShaderProgram shaderProgram;
};

void InitScene(Scene& scene);
void LoadMesh(const std::string& filepath, Scene& scene);
