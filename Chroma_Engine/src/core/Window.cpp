#include "core/Window.h"

#include <iostream>
#include "logger/Logger.h"

namespace chroma
{
	Window::Window(const std::string& name, int width, int height, Uint32 flags) : m_CreationStatus(false)
	{
		// Create Window
		m_WindowInformation.window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (m_WindowInformation.window == nullptr)
		{
			std::cerr << "Could not create Window " << SDL_GetError() << std::endl;
		}

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