#pragma once

#include <map>
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "GameObject.h"
#include "../Graphics/Mesh.h"

class EventDispatcher;
class Input;
class Renderer;
class Simulation;
class Scene;

struct Resources {
	std::map<std::string, Mesh> meshes;
	SDL_Window* window = nullptr;
};

class Game {
public:
	static Game& Instance() {
		static Game instance;
		return instance;
	}

	Game(const Game&) = delete; 
	Game& operator=(const Game&) = delete; 

	int Run(const char* title, int width, int height, bool fullscreen);
private:
	Game() = default;
	bool Init(const char* title, int width, int height, bool fullscreen);
	void Shutdown();
	void SDL2ProcessEvent(SDL_Event& event);
private:
	bool LoadSDL(const char* title, int width, int height, bool fullscreen);
	void LoadSubsystems();
	void LoadResources(Resources& resources);
private:
	bool quit = false;
	SDL_Window* window = nullptr;
	SDL_GLContext glContext = nullptr;

	EventDispatcher* dispatcher = nullptr;
	Input* input = nullptr;
	Renderer* renderer = nullptr;
	Simulation* simulation = nullptr;
	Scene* scene = nullptr;

	Resources resources;
};
