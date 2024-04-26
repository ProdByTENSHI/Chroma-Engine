#pragma once

#include <SDL.h>
#include <eventsystem/EventSystem.h>

namespace chroma
{
	//! Enum that is used to convert SDL Mouse Input Event to actual Buttons
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

		//! -- Gets called every Update Tick
		void Update();

		//! Converts a Mouse Button Event from SDL into a MouseButtonType
		MouseButtonType GetMouseButtonByEvent(SDL_MouseButtonEvent e);

		// -- Application Events
		Event<> OnQuit;                         //! Gets called when the Player requests a Application Exit

		// -- Key Events
		Event<SDL_Keycode> OnKeyDown;			//! Dispatches when a Key is pressed with the KeyCode
		Event<SDL_Keycode> OnKeyUp;				//! Dispatches when a Key is released with the KeyCode

		// -- Mouse Events
		Event<MouseButtonType> OnMouseDown;		//! Dispatches when a Mouse Button is clicked with the Button Type
		Event<MouseButtonType> OnMouseUp;		//! Dispatches when a Mouse Button is released with the Button Type
		Event<int, int> OnMouseMove;			//! Dispatches when the Mouse is moved with the X and Y of the new Position

	private:
		InputManager() {}
		InputManager(const InputManager& other);

		//! Pointer to the Main Window
		SDL_Window* m_Window = nullptr;
	};
}