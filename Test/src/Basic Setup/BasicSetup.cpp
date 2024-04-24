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

	EventHandler<SDL_Keycode> keyDownEvent([](SDL_Keycode key)
		{
			std::cout << SDL_GetKeyName(key) << " was pressed" << std::endl;
		});
	InputManager::GetInstance()->OnKeyDown.Subscribe(keyDownEvent);

	EventHandler<MouseButtonType> mouseDownEvent([](MouseButtonType button)
		{
			std::cout << button << " was pressed" << std::endl;
		});
	InputManager::GetInstance()->OnMouseDown.Subscribe(mouseDownEvent);

	EventHandler<MouseButtonType> mouseUpEvent([](MouseButtonType button)
		{
			std::cout << button << " was released" << std::endl;
		});
	InputManager::GetInstance()->OnMouseUp.Subscribe(mouseUpEvent);

	_app->Update();

	return 0;
}