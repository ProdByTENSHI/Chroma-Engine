#include "core/Application.h"

#include <iostream>

#include <GL/glew.h>
#include "logger/Logger.h"
#include "input/InputManager.h"
#include "resources/ResourceManager.h"
#include "ecs/ECS.h"

namespace chroma
{
	Application::Application(Window* window, Renderer* renderer)
	{
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		// Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cerr << "Could not initialize SDL. SDL Error: " << SDL_GetError() << std::endl;
			return;
		}

		// Create Window
		assert(window->GetCreationStatus() && "Could not initialize SDL Window!");
		m_Window = window;

		// Create OpenGL Context and make current
		SDL_GLContext _glContext = SDL_GL_CreateContext(m_Window->GetWindowInformation().window);
		if (_glContext == NULL)
		{
			std::cerr << "Could not create OpenGL Context " << SDL_GetError() << " : Make sure to set the SDL_WINDOW_OPENGL Window Flag!" << std::endl;
			return;
		}

		SDL_GL_MakeCurrent(window->GetWindowInformation().window, _glContext);

		// Initialize GLEW
		GLenum _glewInitStatus = glewInit();
		if (_glewInitStatus != GLEW_OK)
			std::cerr << "Could not initialize glew. Error " << glewGetErrorString(_glewInitStatus) << std::endl;

		std::cout << "Initialized GLEW " << glewGetString(GLEW_VERSION) << std::endl;

		// Create Renderer
		assert(renderer->GetCreationStatus() && "Could not initialize BGFX");
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

		m_IsRunning = true;
	}

	void Application::Update()
	{
		while (m_IsRunning)
		{
			OnApplicationUpdate.Dispatch();

			InputManager::GetInstance()->Update();
			SDL_Delay(32);
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
		Update();
	}
}