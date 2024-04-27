#include <iostream>
#include <core/Application.h>
#include <input/InputManager.h>
#include <eventsystem/EventSystem.h>

#include "ecs/ECS.h"
#include "ecs/components/Components.h"
#include "ecs/systems/Systems.h"
#include "util/Random.h"

using namespace chroma;

std::shared_ptr<SpriteRendererSystem> spriteRenderSystem;

// Registers all Components and Systems
void initializeECS()
{
	// -- Register Components First
	ECS::GetInstance()->RegisterComponent<TransformComponent>();
	ECS::GetInstance()->RegisterComponent<SpriteComponent>();

	// -- After Component Registration, Register Systems
	spriteRenderSystem = ECS::GetInstance()->RegisterSystem<SpriteRendererSystem>();

	Signature _systemSignature;
	_systemSignature.set(ECS::GetInstance()->GetComponentType<TransformComponent>());
	_systemSignature.set(ECS::GetInstance()->GetComponentType<SpriteComponent>());

	ECS::GetInstance()->SetSystemSignature<SpriteRendererSystem>(_systemSignature);
}

int main(int argc, char* argv[])
{
	Application* _app = new Application();

	Uint32 _windowFlags = SDL_WINDOW_SHOWN;
	Window* _window = new Window("Basic Setup", 1280, 720, _windowFlags);

	Uint32 _renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	Renderer* _renderer = new Renderer(_window->GetWindowInformation().window, _renderFlags);

	EventHandler<> _ecsInitHandler(initializeECS);
	ECS::GetInstance()->OnEcsInitialize.Subscribe(_ecsInitHandler);

	_app->Init(_window, _renderer);

	Scene* _scene = new Scene();
	_app->GetSceneManager().LoadScene(*_scene);

	EventHandler<> _systemUpdate([&_renderer]()
		{
			spriteRenderSystem->Update(_renderer);
		});
	_app->OnApplicationUpdate.Subscribe(_systemUpdate);
	_app->Update();

	return 0;
}