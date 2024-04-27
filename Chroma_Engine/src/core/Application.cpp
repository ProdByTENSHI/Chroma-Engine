#include "core/Application.h"

#include <iostream>

#include "logger/Logger.h"
#include "input/InputManager.h"
#include "resources/ResourceManager.h"
#include "ecs/ECS.h"

namespace chroma
{
	Application::Application()
	{
		// Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			Logger::GetInstance()->Log("Could not initialize SDL");
			return;
		}

		m_IsRunning = true;
	}

	void Application::Init(Window* window, Renderer* renderer)
	{
		// Create Window
		assert(window->GetCreationStatus() && "Could not initialize SDL Window!");

		// Create Renderer
		assert(renderer->GetCreationStatus() && "Could not initialize BGFX");

		m_Window = window;
		m_Renderer = renderer;

		ResourceManager::GetInstance()->Init(m_Renderer);

		ECS::GetInstance()->Init();

		m_SceneManager = new SceneManager();

		// Lambda Function for the On Quit Event
		EventHandler<> _quitFunction = EventHandler<>([this]()
			{
				m_IsRunning = false;
				OnApplicationEnd.Dispatch();

				Logger::GetInstance()->Log("Chroma Engine shutdown");

				SDL_Quit();
			});
		InputManager::GetInstance()->OnQuit += _quitFunction;

		// Dispatch the Start Event
		OnApplicationStart.Dispatch();

		Logger::GetInstance()->Log("Chroma Engine initialized");
	}

	void Application::Update()
	{
		while (m_IsRunning)
		{
			OnApplicationUpdate.Dispatch();

			InputManager::GetInstance()->Update();
			FixedUpdate();
		}
	}

	void Application::FixedUpdate()
	{
		OnApplicationFixedUpdate.Dispatch();

		Render();
	}

	void Application::Render()
	{
		// Render
		SDL_Delay(32);
		Update();
	}
}