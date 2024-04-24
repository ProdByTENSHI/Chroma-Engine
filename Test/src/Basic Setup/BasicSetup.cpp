#include <iostream>
#include <core/Application.h>
#include <input/InputManager.h>
#include <eventsystem/EventSystem.h>

using namespace chroma;

int main(int argc, char* argv[])
{
	Application* _app = new Application();

	Uint32 _windowFlags = SDL_WINDOW_SHOWN;
	Window* _window = new Window("Basic Setup", 1280, 720, _windowFlags);

	Uint32 _renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	Renderer* _renderer = new Renderer(_window->GetWindowInformation().window, _renderFlags);

	_app->Init(_window, _renderer);

	EventHandler<int, int> _mousePosition([](int x, int y)
		{
			std::cout << "Mouse Position X: " << x << " Y: " << y << std::endl;
		});

	InputManager::GetInstance()->OnMouseMove.Subscribe(_mousePosition);

	_app->Update();

	return 0;
}