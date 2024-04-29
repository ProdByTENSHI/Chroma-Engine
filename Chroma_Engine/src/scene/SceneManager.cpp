#include "scene/SceneManager.h"

#include "ecs/components/Components.h"
#include "util/Random.h"
#include "logger/Logger.h"

namespace chroma
{
	// -- Scene Management

	bool SceneManager::AddScene(Scene& scene, int index)
	{
		if (IsSceneOnIndex(index))
		{
			Logger::GetInstance()->Log("Scene already on Index " + index);
			return false;
		}

		m_Scenes.insert({ index, &scene });
	}

	void SceneManager::RemoveScene(int index)
	{
		for (auto const& pair : m_Scenes)
		{
			if (pair.first == index)
				m_Scenes[index] = nullptr;
		}
	}

	void SceneManager::RemoveScene(Scene& scene)
	{
		for (auto const& pair : m_Scenes)
		{
			if (pair.second == &scene)
				m_Scenes[pair.first] = nullptr;
		}
	}

	// TODO: Load actual Scene Data -- This is only placeholder
	void LoadSceneFunc()
	{
		for (int i = 0; i < MAX_ENTITIES; i++)
		{
			Entity _entity = ECS::GetInstance()->CreateEntity();
			TransformComponent _transform;
			_transform.position = Vector2((float)Random::GetInt(0, 1920), (float)Random::GetInt(0, 1280));
			_transform.size = Vector2(100, 100);
			ECS::GetInstance()->AddComponent<TransformComponent>(_entity, _transform);
		}
	}

	void SceneManager::LoadScene(Scene& scene)
	{
		m_IsCurrentlyLoading = true;

		// Block Main Thread
		std::thread _loadThread(LoadSceneFunc);
		_loadThread.join();

		std::cout << "Finished loading Scene" << std::endl;

		OnSceneLoad.Dispatch(scene);
		m_IsCurrentlyLoading = false;
	}

	void SceneManager::LoadScene(uint32_t index)
	{
		for (auto const& pair : m_Scenes)
		{
			if (pair.first == index)
				LoadScene(*pair.second);
		}
	}

	// -- Utility Functions

	Scene* SceneManager::GetSceneByIndex(int index)
	{
		for (auto const& pair : m_Scenes)
		{
			if (pair.first == index)
				return pair.second;
		}

		return nullptr;
	}

	int SceneManager::GetIndexByScene(Scene& scene)
	{
		for (auto const& pair : m_Scenes)
		{
			if (pair.second == &scene)
				return pair.first;
		}

		return -1;
	}

	bool SceneManager::IsSceneOnIndex(int index)
	{
		for (auto const& pair : m_Scenes)
		{
			if (pair.first == index && pair.second != nullptr)
				return true;
		}

		return false;
	}

	int SceneManager::GetNextFreeIndex()
	{
		for (auto const& pair : m_Scenes)
		{
			if (pair.second == nullptr)
				return pair.first;
		}

		std::cout << "oh oh" << std::endl;
		return -1;
	}

	bool SceneManager::IsCurrentlyLoading()
	{
		return m_IsCurrentlyLoading;
	}
}