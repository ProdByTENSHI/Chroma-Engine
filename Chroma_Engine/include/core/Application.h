#pragma once

#include "Window.h"
#include "rendering/Renderer.h"

#include <eventsystem/EventSystem.h>

namespace chroma
{
	class Application
	{
	public:
		// Before doing anything SDL Related the Application has to be created
		Application();

		// Initializes Engine related Manager(Window, Renderer...)
		void Init(Window* window, Renderer* renderer);

		// Updates as often as possible - Variable Time Step
		void Update();

		// Updates in fixed intervals. Use for Physics and Collision related Stuff - Fixed Time Step
		void FixedUpdate();

		// Renders the final Screen
		void Render();

		// -- Getter

		const Window& GetWindow() const { return *m_Window; }
		const Renderer& GetRenderer() const { return *m_Renderer; }

		// -- Events

		Event<> OnApplicationStart;
		Event<> OnApplicationUpdate;
		Event<> OnApplicationFixedUpdate;
		Event<> OnApplicationEnd;

	private:
		Window* m_Window = nullptr;
		Renderer* m_Renderer = nullptr;

		bool m_IsRunning = false;

	};
}