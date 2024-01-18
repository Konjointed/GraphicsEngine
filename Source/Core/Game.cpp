#include "Game.h"

#include <iostream>

#include "../Events/EventDispatcher.h"
#include "../Events/KeyboardEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/ApplicationEvent.h"

#include "Scene.h"
#include "Renderer.h"
#include "Input.h"

int Game::Run(const char* title, int width, int height, bool fullscreen)
{
	if (!Init(title, width, height, fullscreen))
		return -1;

	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			//ImGui_ImplSDL2_ProcessEvent(&event);
			SDL2ProcessEvent(event);
		}

		static float lastFrameTime = 0.0f;

		float time = SDL_GetTicks() / 1000.0f;
		float timestep = time - lastFrameTime;
		lastFrameTime = time;

		//static int frameCount = 0;
		//static float totalTime = 0.0f;
		// 
		//totalTime += timestep;
		//frameCount++;

		//if (totalTime >= 1.0f) {
		//	float fps = frameCount / totalTime;
		//	std::cout << "FPS: " << fps << std::endl;
		//	frameCount = 0;
		//	totalTime = 0.0f;
		//}	

		Update(timestep);
		Render();
		input->EndFrame();
	}

	Shutdown();

	return 0;
}

bool Game::Init(const char* title, int width, int height, bool fullscreen)
{
	//-----------------------------------------------------------------------------
	// Initialzie SDL
	//-----------------------------------------------------------------------------
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL error on initialization: " << SDL_GetError() << "\n";
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//-----------------------------------------------------------------------------
	// Create sdl window
	//-----------------------------------------------------------------------------
	const Uint32 windowFlags = (SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_RESIZABLE : 0));
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);
	if (!window) {
		std::cout << "SDL error on create window: " << SDL_GetError() << "\n";
		return false;
	}
	//-----------------------------------------------------------------------------
	// Create opengl context
	//-----------------------------------------------------------------------------
	glContext = SDL_GL_CreateContext(window);
	if (!glContext) {
		std::cout << "SDL GL error on create context: " << SDL_GetError() << "\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}
	//-----------------------------------------------------------------------------
	// Load opengl functions and pointers
	//-----------------------------------------------------------------------------
	if (!gladLoadGL()) {
		std::cout << "GLAD Initialization Error\n";
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}
	//-----------------------------------------------------------------------------
	// Create subsystems
	//-----------------------------------------------------------------------------
	dispatcher = new EventDispatcher();

	scene = new Scene();
	renderer = new Renderer();
	input = new Input(*dispatcher);

	// TODO: Move this to a scene loader?
	InitScene(*scene);
	LoadMesh("Resources/Meshes/cube.obj", *scene);

	glEnable(GL_DEPTH_TEST);

	return true;
}

void Game::Shutdown()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	delete dispatcher;
	delete scene;
	delete renderer;
	delete input;
}

void Game::Update(float timestep)
{
	scene->camera.Update(timestep, *input);

	if (input->IsKeyDown(SDLK_ESCAPE)) {
		quit = true;
	}
}

void Game::Render()
{
	renderer->Draw(window, *scene);
}

void Game::SDL2ProcessEvent(SDL_Event& event)
{
	switch (event.type) {
	case SDL_WINDOWEVENT:
		if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
			int newWidth = event.window.data1;
			int newHeight = event.window.data2;
			glViewport(0, 0, newWidth, newHeight);
		}
		break;
	case SDL_QUIT:
	{
		quit = true;
	}
		break;
	case SDL_KEYDOWN:
	{
		KeyboardPressEvent evt(event.key.keysym.sym);
		dispatcher->Dispatch(evt);
	}
		break;
	case SDL_KEYUP:
	{
		KeyboardReleaseEvent evt(event.key.keysym.sym);
		dispatcher->Dispatch(evt);
	}
		break;
	case SDL_MOUSEBUTTONDOWN:
	{
		MouseButtonPressEvent evt(event.button.button);
		dispatcher->Dispatch(evt);
	}
		break;
	case SDL_MOUSEBUTTONUP:
	{
		MouseButtonReleaseEvent evt(event.button.button);
		dispatcher->Dispatch(evt);
	}
		break;
	case SDL_MOUSEWHEEL:
	{
	}
		break;
	case SDL_MOUSEMOTION:
	{
		// what is xrel and yrel?
		MouseMoveEvent evt(event.motion.x, event.motion.y);
		dispatcher->Dispatch(evt);
	}
		break;
	}
}
