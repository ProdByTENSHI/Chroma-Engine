#include "core/Application.h"

#include <iostream>

#include "logger/Logger.h"
#include "input/InputManager.h"
#include "ecs/ECS.h"

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

		ECS::GetInstance()->Init();

		// Lambda Function for the On Quit Event
		EventHandler<> _quitFunction = EventHandler<>([this]()
			{
				m_IsRunning = false;
				OnApplicationEnd.Dispatch();

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
			m_Renderer->Prepare();
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
		m_Renderer->Present();

		Update();
	}
}