#include <iostream>
#include <core/Application.h>

using namespace chroma;

int main(int argc, char* argv[])
{
	Application* _app = new Application();

	Uint32 _windowFlags = SDL_WINDOW_SHOWN;
	Window* _window = new Window("Basic Setup", 1280, 720, _windowFlags);

	Uint32 _renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	Renderer* _renderer = new Renderer(_window->GetWindowInformation().window, _renderFlags);

	AppInformation _appInfo;
	_appInfo.window = _window;
	_appInfo.renderer = _renderer;

	_app->Init(_appInfo);
	_app->Update();

	return 0;
}