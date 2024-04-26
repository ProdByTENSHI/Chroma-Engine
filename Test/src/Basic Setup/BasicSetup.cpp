#include <iostream>
#include <core/Application.h>
#include <input/InputManager.h>
#include <eventsystem/EventSystem.h>

#include "ecs/ECS.h"
#include "ecs/components/Components.h"
#include "ecs/systems/Systems.h"
#include "util/Random.h"

using namespace chroma;

int main(int argc, char* argv[])
{
	Application* _app = new Application();

	Uint32 _windowFlags = SDL_WINDOW_SHOWN;
	Window* _window = new Window("Basic Setup", 1280, 720, _windowFlags);

	Uint32 _renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	Renderer* _renderer = new Renderer(_window->GetWindowInformation().window, _renderFlags);

	_app->Init(_window, _renderer);

	// -- Register Components First
	ECS::GetInstance()->RegisterComponent<TransformComponent>();
	ECS::GetInstance()->RegisterComponent<SpriteComponent>();

	// -- After Component Registration, Register Systems
	auto _spriteRendererSystem = ECS::GetInstance()->RegisterSystem<SpriteRendererSystem>();

	Signature _systemSignature;
	_systemSignature.set(ECS::GetInstance()->GetComponentType<TransformComponent>());
	_systemSignature.set(ECS::GetInstance()->GetComponentType<SpriteComponent>());

	ECS::GetInstance()->SetSystemSignature<SpriteRendererSystem>(_systemSignature);

	// -- Create Entities and do whatever you want to
	int _entitiesToGenerate = MAX_ENTITIES;
	for (int i = 0; i < _entitiesToGenerate; i++)
	{
		Entity _entity = ECS::GetInstance()->CreateEntity();
		TransformComponent _transform;
		_transform.position = glm::vec2((float)Random::GetInt(0, 1920), (float)Random::GetInt(0, 1280));
		_transform.size = glm::vec2(250, 250);
		ECS::GetInstance()->AddComponent<TransformComponent>(_entity, _transform);
		ECS::GetInstance()->AddComponent<SpriteComponent>(_entity, SpriteComponent("res/test.png"));
	}

	EventHandler<> _systemUpdate([&_renderer, &_spriteRendererSystem]()
		{
			_spriteRendererSystem->Update(_renderer);
		});
	_app->OnApplicationUpdate.Subscribe(_systemUpdate);
	_app->Update();

	return 0;
}