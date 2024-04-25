#pragma once

#include "ecs/ECS_Definitions.h"

#include <array>
#include <unordered_map>
#include <assert.h>

namespace chroma
{
	// -- Component Array
	class IComponentArray
	{
		virtual ~IComponentArray() = default;

		// Gets called when an Entity is destroyed to let the ComponentArray(s) know to update their Maps
		virtual void EntityDestroyed(Entity entity) = 0;
	};

	template <typename T> class ComponentArray : public IComponentArray
	{
	public:
		// Inserts a Component at Entity's Index and Update Maps
		void Insert(Entity entity, T component)
		{
			assert(entity != m_EntityToIndex.find(entity) && "Entity ID not valid!");

			size_t _newIndex = m_ValidEntries;

			m_EntityToIndex[entity] = _newIndex;
			m_IndexToEntity[_newIndex] = entity;
			m_ComponentArray[_newIndex] = component:

			++m_ValidEntries;
		}

		// Removes the Component and the Entity
		void Remove(Entity entity)
		{
			assert(entity != m_EntityToIndex.find(entity) && "Entity ID not valid!");

			// Copy last Element into entities Index
			size_t _removedEntityIndex = m_EntityToIndex[entity];
			size_t _lastElement = m_ValidEntries - 1;

			m_ComponentArray[_removedEntityIndex] = m_ComponentArray[_lastElement];

			// Update Maps
			Entity _lastEntity = m_IndexToEntity[_lastElement];

			m_EntityToIndex[_lastEntity] = _removedEntityIndex;
			m_IndexToEntity[_removedEntityIndex] = _lastEntity;

			// Remove last Entry
			m_EntityToIndex.erase(_lastEntity);
			m_IndexToEntity.erase(_lastElement);

			--m_ValidEntries;
		}

		// Returns a Reference to the associated Component of the given Entity
		T& GetComponent(Entity entity)
		{
			assert(entity != m_EntityToIndex.find(entity) && "Entity ID not valid!");

			return m_ComponentArray[m_EntityToIndex[entity]];
		}

		void EntityDestroyed(Entity entity) override
		{
			assert(entity != m_EntityToIndex.find(entity) && "Entity ID not valid!");

			if (std::find(m_EntityToIndex.begin, m_EntityToIndex.end, entity) != m_EntityToIndex.end)
				Remove(entity);
		}

	private:
		// A packed array that holds all Components of this type
		// Each Entity has a unique Spot in the Compnent Array
		std::array<T, MAX_ENTITIES> m_ComponentArray;

		// Unordered Map that returns the index into the m_ComponentArray by the Entity(ID)
		std::unordered_map<Entity, size_t> m_EntityToIndex;

		// An Unordered Map that returns the Entity by the index of the m_ComponentArray
		std::unordered_map<size_t, Entity> m_IndexToEntity;

		// Number of Valid Entries in the m_ComponentArray
		size_t m_ValidEntries = 0;
	};

	// -- Component Manager
	class ComponentManager
	{
	public:
		// -- Singleton Setup

		static ComponentManager* GetInstance()
		{
			if (instance == nullptr)
				instance = new ComponentManager();

			return instance;
		}

	private:
		// -- Singleton Setup

		static ComponentManager* instance;

		ComponentManager();
		ComponentManager(const ComponentManager& other);
	};
}