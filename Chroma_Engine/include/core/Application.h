#pragma once

#include "Window.h"
#include "rendering/Renderer.h"
#include "scene/SceneManager.h"

#include <eventsystem/EventSystem.h>

namespace chroma
{
	class Application
	{
	public:
		//! Initializes the Libraries and the Engine Systems
		Application(Window* window, Renderer* renderer);

		//! Updates as often as possible - Variable Time Step
		void Update();

		//! Updates in fixed intervals. Use for Physics and Collision related Stuff - Fixed Time Step
		void FixedUpdate();

		//! Renders the final Screen
		void Render();

		// -- Getter

		inline const Window& GetWindow() const { return *m_Window; }
		inline const Renderer& GetRenderer() const { return *m_Renderer; }
		inline SceneManager& GetSceneManager() const { return *m_SceneManager; }

		// -- Events

		Event<> OnApplicationStart;
		Event<> OnApplicationUpdate;
		Event<> OnApplicationFixedUpdate;
		Event<> OnApplicationEnd;

	private:
		Window* m_Window = nullptr;
		Renderer* m_Renderer = nullptr;
		SceneManager* m_SceneManager = nullptr;

		bool m_IsRunning = false;

	};
}