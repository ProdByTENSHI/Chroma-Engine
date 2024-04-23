#include <iostream>
#include <core/Application.h>
#include <eventsystem/EventSystem.h>

using namespace chroma;

void keyDown(SDL_Keycode key)
{
	if (key == SDLK_w)
	{
		std::cout << "Bing Bong der Eiermann ist da" << std::endl;
		return;
	}

	std::cout << SDL_GetKeyName(key) << " was pressed down!" << std::endl;
}

void keyUp(SDL_Keycode key)
{
	std::cout << SDL_GetKeyName(key) << " was released!" << std::endl;
}

int main(int argc, char* argv[])
{
	Application* _app = new Application();

	Uint32 _windowFlags = SDL_WINDOW_SHOWN;
	Window* _window = new Window("Basic Setup", 1280, 720, _windowFlags);

	Uint32 _renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	Renderer* _renderer = new Renderer(_window->GetWindowInformation().window, _renderFlags);

	_app->Init(_window, _renderer);

	EventHandler<SDL_Keycode> _keyDownEvent = EventHandler<SDL_Keycode>(keyDown);
	EventHandler<SDL_Keycode> _keyReleaseEvent = EventHandler<SDL_Keycode>(keyUp);

	_app->GetInputManager()->OnKeyDown += _keyDownEvent;
	_app->GetInputManager()->OnKeyUp += _keyReleaseEvent;

	_app->Update();

	return 0;
}