#pragma once

#include <SDL.h>
#include <string>

namespace chroma
{
	struct WindowInformation
	{
		SDL_Window* window;

		std::string name;

		int width;
		int height;
	};

	class Window
	{
	public:
		Window(const std::string& name, int width, int height, Uint32 flags);
		~Window();

		//! Returns if the Window Creation was successful
		inline bool GetCreationStatus()
		{
			return m_CreationStatus;
		}

		//! Returns the Window Information
		inline const WindowInformation& GetWindowInformation() const
		{
			return m_WindowInformation;
		}

	private:
		WindowInformation m_WindowInformation;

		bool m_CreationStatus;

	};
}