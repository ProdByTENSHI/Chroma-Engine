#include "ecs/ECS.h"

namespace chroma
{
	static ECS* instance;

	ECS* ECS::GetInstance()
	{
		if (instance == nullptr)
			instance = new ECS();

		return instance;
	}

	void ECS::Init()
	{
		m_EntityManager = new EntityManager();
		m_ComponentManager = new ComponentManager();
		m_SystemManager = new SystemManager();

		OnEcsInitialize.Dispatch();
	}

	Entity ECS::CreateEntity()
	{
		return m_EntityManager->CreateEntity();
	}

	void ECS::DestroyEntity(Entity entity)
	{
		m_EntityManager->DestroyEntity(entity);
		m_ComponentManager->EntityDestroyed(entity);
		m_SystemManager->EntityDestroyed(entity);
	}
}