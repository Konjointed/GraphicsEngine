#pragma once

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Scene;
struct Mesh;

class Renderer {
public:
	void Draw(SDL_Window* window, Scene& scene);
private:
	void BindMesh(const Mesh& mesh);
};