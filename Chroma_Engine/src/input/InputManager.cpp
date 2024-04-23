#include "input/InputManager.h"

#include <iostream>

namespace chroma
{
	static InputManager* instance = nullptr;

	InputManager* InputManager::GetInstance()
	{
		if (instance == nullptr)
			instance = new InputManager();

		return instance;
	}

	void InputManager::HandleInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				OnQuit.Dispatch();
				break;

			case SDL_KEYDOWN:
				OnKeyDown.Dispatch(e.key.keysym.sym);
				break;

			case SDL_KEYUP:
				OnKeyUp.Dispatch(e.key.keysym.sym);
				break;
			}
		}

		// Update Mouse State
		int _x, _y;
		SDL_GetMouseState(&_x, &_y);

		if (m_MouseX != _x || m_MouseY != _y)
		{
			m_MouseX = _x;
			m_MouseY = _y;

			OnMouseMove.Dispatch(m_MouseX, m_MouseY);
		}
	}
}