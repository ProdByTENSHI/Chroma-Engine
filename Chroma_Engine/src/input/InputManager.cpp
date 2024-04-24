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

	MouseButtonType InputManager::GetMouseButtonByEvent(SDL_MouseButtonEvent e)
	{
		switch (e.button)
		{
		case SDL_BUTTON_LEFT:
			return MouseButtonType::Left;

		case SDL_BUTTON_MIDDLE:
			return MouseButtonType::Middle;

		case SDL_BUTTON_RIGHT:
			return MouseButtonType::Right;
		}
	}

	void InputManager::Update()
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

			case SDL_MOUSEMOTION:
				int _x, _y;
				SDL_GetMouseState(&_x, &_y);
				OnMouseMove.Dispatch(_x, _y);
				break;

			case SDL_MOUSEBUTTONDOWN:
				OnMouseDown.Dispatch(GetMouseButtonByEvent(e.button));
				break;

			case SDL_MOUSEBUTTONUP:
				OnMouseUp.Dispatch(GetMouseButtonByEvent(e.button));
				break;
			}
		}
	}
}