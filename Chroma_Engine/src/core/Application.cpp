#include "core/Application.h"

#include <iostream>

#include "logger/Logger.h"
#include "input/InputManager.h"

namespace chroma
{
	Application::Application()
	{
		// Initialize SDL and other Libraries
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			Logger::GetInstance()->Log("Could not initialize SDL");
			return;
		}

		m_IsRunning = true;
	}

	void Application::Init(Window* window, Renderer* renderer)
	{
		if (!window->GetCreationStatus())
		{
			Logger::GetInstance()->Log("Window could not be created");
			m_IsRunning = false;

			return;
		}

		m_Window = window;

		if (!renderer->GetCreationStatus())
		{
			Logger::GetInstance()->Log("Renderer could not be created");
			m_IsRunning = false;

			return;
		}

		m_Renderer = renderer;

		// Lambda Function for the On Quit Event
		EventHandler<> _quitFunction = EventHandler<>([this]()
			{
				m_IsRunning = false;

				SDL_Quit();
			});
		InputManager::GetInstance()->OnQuit += _quitFunction;

		Logger::GetInstance()->Log("Chroma Engine initialized");
	}

	void Application::Update()
	{
		while (m_IsRunning)
		{
			m_Renderer->Prepare();

			InputManager::GetInstance()->HandleInput();

			// Todo: Render everything that needs to be shown

			m_Renderer->Present();

			SDL_Delay(16); // Todo: Replace with actual Fixed Update
		}
	}
}