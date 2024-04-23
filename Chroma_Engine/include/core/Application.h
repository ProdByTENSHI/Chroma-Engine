#pragma once

#include "Window.h"
#include "rendering/Renderer.h"
#include "input/InputManager.h"

namespace chroma
{
	class Application
	{
	public:
		// Before doing anything SDL Related the Application has to be created
		Application();

		void Init(Window* window, Renderer* renderer);
		void Update();

		// -- Getter
		const Window& GetWindow() const { return *m_Window; }
		const Renderer& GetRenderer() const { return *m_Renderer; }
		InputManager* GetInputManager() const { return m_InputManager; }

	private:
		Window* m_Window = nullptr;
		Renderer* m_Renderer = nullptr;
		InputManager* m_InputManager = nullptr;

		bool m_IsRunning = false;

	};
}