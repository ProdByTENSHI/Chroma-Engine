#pragma once

#include <thread>
#include <unordered_map>

#include "eventsystem/EventSystem.h"
#include "scene/Scene.h"

namespace chroma
{
	//! The Scene Manager handles Scene Serialization, Application Scene State and Dispatches Events on certain Scene Actions
	class SceneManager
	{
	public:
		// -- Scene Management
		//! Tries to add the Scene to the Scene Container with the given Index
		//! @param[in] scene The Scene to add
		//! @param[in] index The Index the Scene should be added with
		//! @return bool Returns if the Scene was added to the Map. Can fail if index is already used by other Scene
		bool AddScene(Scene& scene, int index);

		//! Removes the Scene with the given Index
		void RemoveScene(int index);

		//! Removes the Scene by a Reference to the Scene
		void RemoveScene(Scene& scene);

		//! Loads the given Scene and destroys the old Scene by Scene Reference
		//! Uses a different Thread to load the Scene and blocks the main thread while doing so
		void LoadScene(Scene& scene);

		//! Loads the given Scene and destroys the old Scene by Index
		void LoadScene(uint32_t index);

		// -- Utillity Functions
		//! Returns a pointer to the Scene by its Index
		Scene* GetSceneByIndex(int index);

		//! Returns the Index by Scene
		int GetIndexByScene(Scene& scene);

		//! Returns wether a Scene uses this Index or not
		bool IsSceneOnIndex(int index);

		//! Returns the next free Scene Index
		int GetNextFreeIndex();

		//! Returns if the Scene Manager is currently loading Scene
		bool IsCurrentlyLoading();

		// -- Events
		//! Is Dispatched when a new Scene is loaded
		//! @param[Scene&] scene A reference to the Scene that was loaded
		Event<Scene&> OnSceneLoad;

		//! Is Dispatched when the current Scene is destroyed
		Event<> OnCurrentSceneDestroyed;

	private:
		//! Unordered Map that holds all Scene Pointers by their Index
		//! Each Index is unique meaning no Index can have more that one Scene
		std::unordered_map<int, Scene*> m_Scenes;

		//! The currently active Scene
		Scene* m_CurrentScene = nullptr;

		//! Stores the State if the Scene Manager is currently loading a Scene
		bool m_IsCurrentlyLoading = false;

	};
}