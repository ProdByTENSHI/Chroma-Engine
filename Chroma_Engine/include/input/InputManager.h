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

		// -- Application Events
		Event<> OnQuit;

		// -- Key Events
		Event<SDL_Keycode> OnKeyDown;
		Event<SDL_Keycode> OnKeyUp;

	private:
		SDL_Window* m_Window = nullptr;
	};
}