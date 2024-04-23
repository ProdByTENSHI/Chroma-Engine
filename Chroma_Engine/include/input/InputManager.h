#pragma once

#include <SDL.h>
#include <eventsystem/EventSystem.h>

namespace chroma
{
	class InputManager
	{
	public:
		InputManager(SDL_Window* window);

		void HandleInput();

		Event<> OnQuit;

	private:
		SDL_Window* m_Window = nullptr;
	};
}