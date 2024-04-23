#pragma once

#include <SDL.h>
#include <eventsystem/EventSystem.h>

namespace chroma
{
	class InputManager
	{
	public:
		static InputManager* GetInstance();

		void HandleInput();

		// -- Application Events
		Event<> OnQuit;

		// -- Key Events
		Event<SDL_Keycode> OnKeyDown;
		Event<SDL_Keycode> OnKeyUp;

		// -- Mouse Events
		Event<int, int> OnMouseMove;

	private:
		InputManager() : m_MouseX(0), m_MouseY(0) {}
		InputManager(const InputManager& other);

		int m_MouseX;
		int m_MouseY;

		SDL_Window* m_Window = nullptr;
	};
}