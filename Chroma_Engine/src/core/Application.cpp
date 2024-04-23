#include "core/Application.h"

#include "logger/Logger.h"

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
		m_InputManager = new InputManager(window->GetWindowInformation().window);

		Logger::GetInstance()->Log("Chroma Engine initialized");
	}

	void Application::Update()
	{
		while (m_IsRunning)
		{
			m_Renderer->Prepare();

			// Todo: Handle Input

			// Todo: Render everything that needs to be shown

			m_Renderer->Present();

			SDL_Delay(16); // Todo: Replace with actual Fixed Update
		}
	}

	void Application::Quit()
	{
		delete m_Renderer;
		delete m_Window;

		SDL_Quit();
	}
}