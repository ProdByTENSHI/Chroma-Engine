#include "ecs/ECS.h"

#include <iostream>
#include <assert.h>

#include "logger/Logger.h"

namespace chroma
{
	static EntityManager* entityManagerInstance;

	EntityManager* EntityManager::GetInstance()
	{
		if (entityManagerInstance == nullptr)
			entityManagerInstance = new EntityManager();

		return entityManagerInstance;
	}

	EntityManager::EntityManager()
	{
		for (int i = 0; i < MAX_ENTITIES; i++)
		{
			m_AvaiableEntities.push(i);
		}
	}

	// -- Entity Lifetime
	Entity EntityManager::CreateEntity()
	{
		assert(m_EntitiesInScene < MAX_ENTITIES && "Too many Entities in Scene!");

		Entity _entity = m_AvaiableEntities.front();
		m_AvaiableEntities.pop();

		++m_EntitiesInScene;

		return _entity;
	}

	void EntityManager::DestroyEntity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity not Destroyed! Entity out of Range");

		// Invalidate the Signature(Sets all bits to 0 / False)
		m_Signatures[entity].reset();

		// Returns the Entity to the avaiable Entities
		m_AvaiableEntities.push(entity);
		--m_EntitiesInScene;
	}

	// -- Signature
	void EntityManager::SetSignature(Entity entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Signature not Set! Entity out of Range");

		m_Signatures[entity] = signature;
	}

	Signature EntityManager::GetSignature(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Cannot retrieve Signature! Entity out of Range");

		return m_Signatures[entity];
	}
}