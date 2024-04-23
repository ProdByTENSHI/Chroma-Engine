#include "core/Window.h"

#include "logger/Logger.h"

namespace chroma
{
	Window::Window(const std::string& name, int width, int height, Uint32 flags)
	{
		// Create Window
		m_WindowInformation.window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (m_WindowInformation.window == nullptr)
		{
			Logger::GetInstance()->Log("Window could not be created!");
			m_CreationStatus = false;
		}

		// Create OpenGL Context
		SDL_GLContext context = SDL_GL_CreateContext(m_WindowInformation.window);

		// Populate Window Information Struct
		m_WindowInformation.name = name;
		m_WindowInformation.width = width;
		m_WindowInformation.height = height;

		m_CreationStatus = true;
	}

	Window::~Window()
	{
		SDL_DestroyWindow(m_WindowInformation.window);
		delete m_WindowInformation.window;
	}
}