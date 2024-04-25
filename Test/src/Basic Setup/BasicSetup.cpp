#include <iostream>
#include <core/Application.h>
#include <input/InputManager.h>
#include <eventsystem/EventSystem.h>

#include "ecs/ECS.h"
#include "ecs/Components/Components.h"

using namespace chroma;

int main(int argc, char* argv[])
{
	Application* _app = new Application();

	Uint32 _windowFlags = SDL_WINDOW_SHOWN;
	Window* _window = new Window("Basic Setup", 1280, 720, _windowFlags);

	Uint32 _renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	Renderer* _renderer = new Renderer(_window->GetWindowInformation().window, _renderFlags);

	_app->Init(_window, _renderer);

	ECS::GetInstance()->RegisterComponent<TransformComponent>();
	ECS::GetInstance()->RegisterComponent<SpriteComponent>();

	Entity _entity = ECS::GetInstance()->CreateEntity();

	_app->Update();

	return 0;
}