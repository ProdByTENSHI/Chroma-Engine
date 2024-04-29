#include <iostream>
#include <core/Application.h>
#include <input/InputManager.h>
#include <eventsystem/EventSystem.h>

#include "ecs/ECS.h"
#include "ecs/components/Components.h"
#include "ecs/systems/Systems.h"
#include "util/Random.h"

using namespace chroma;

// Registers all Components and Systems
void initializeECS()
{
	// -- Register Components First
	ECS::GetInstance()->RegisterComponent<TransformComponent>();
}

int main(int argc, char* argv[])
{
	Application* _app = new Application();

	Uint32 _windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
	Window* _window = new Window("Basic Setup", 1280, 720, _windowFlags);

	Uint32 _renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	Renderer* _renderer = new Renderer();

	EventHandler<> _ecsInitHandler(initializeECS);
	ECS::GetInstance()->OnEcsInitialize.Subscribe(_ecsInitHandler);

	_app->Init(_window, _renderer);

	Scene* _scene = new Scene();
	_app->GetSceneManager().LoadScene(*_scene);

	_app->Update();

	return 0;
}