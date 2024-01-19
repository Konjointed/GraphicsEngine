#pragma once

#include <string>
#include <vector>

#include "../Graphics/ShaderProgram.h"

class GameObject;

class Scene {
public:
	std::vector<GameObject> objects;
	ShaderProgram shaderProgram;

	Scene() = default;

	GameObject& CreateGameObject(const std::string& name);

	void DestroyGameObject(GameObject object);
};

void CreateScene(Scene& scene);