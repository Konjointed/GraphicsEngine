#pragma once

#include <memory>

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Scene;
class Renderer;
class Input;
class EventDispatcher;

class Game {
public:
	static Game& Instance() {
		static Game instance;
		return instance;
	}

	Game(const Game&) = delete; // Delete copy constructor
	Game& operator=(const Game&) = delete; // Delete copy assignment operator

	int Run(const char* title, int width, int height, bool fullscreen);
private:
	Game() = default;
	bool Init(const char* title, int width, int height, bool fullscreen);
	void Shutdown();
	void Update(float timestep);
	void Render();
	void SDL2ProcessEvent(SDL_Event& event);
private:
	bool quit = false;
	SDL_Window* window = nullptr;
	SDL_GLContext glContext = nullptr;

	EventDispatcher* dispatcher;

	Scene* scene;
	Renderer* renderer;
	Input* input;
};
