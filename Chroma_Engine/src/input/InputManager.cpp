#include "input/InputManager.h"

#include <iostream>

namespace chroma
{
	InputManager::InputManager(SDL_Window* window)
	{
		m_Window = window;
	}

	void InputManager::HandleInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
			case SDLK_ESCAPE:
				OnQuit.Dispatch();
				break;
			}
		}
	}
}