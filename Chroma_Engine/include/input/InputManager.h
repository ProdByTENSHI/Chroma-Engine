#pragma once

#include <SDL.h>
#include <eventsystem/EventSystem.h>

namespace chroma
{
	enum MouseButtonType
	{
		Left = 0,
		Middle = 1,
		Right = 2
	};

	class InputManager
	{
	public:
		static InputManager* GetInstance();

		void Update();
		MouseButtonType GetMouseButtonByEvent(SDL_MouseButtonEvent e);

		// -- Application Events
		Event<> OnQuit;

		// -- Key Events
		Event<SDL_Keycode> OnKeyDown;			// Dispatches when a Key is pressed with the KeyCode
		Event<SDL_Keycode> OnKeyUp;				// Dispatches when a Key is released with the KeyCode

		// -- Mouse Events
		Event<MouseButtonType> OnMouseDown;		// Dispatches when a Mouse Button is clicked with the Button Type
		Event<MouseButtonType> OnMouseUp;		// Dispatches when a Mouse Button is released with the Button Type
		Event<int, int> OnMouseMove;			// Dispatches when the Mouse is moved with the X and Y of the new Position

	private:
		InputManager() {}
		InputManager(const InputManager& other);

		SDL_Window* m_Window = nullptr;
	};
}