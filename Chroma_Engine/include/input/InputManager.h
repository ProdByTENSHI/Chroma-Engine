#pragma once

#include <SDL.h>

namespace chroma
{
	class InputManager
	{
	public:
		InputManager(SDL_Window* window);

		void HandleInput();

	private:
		SDL_Window* m_Window = nullptr;
	};
}