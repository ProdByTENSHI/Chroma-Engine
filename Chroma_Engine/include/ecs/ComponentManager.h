#pragma once

#include "ecs/ECS_Definitions.h"

#include <array>
#include <unordered_map>
#include <memory>
#include <assert.h>

namespace chroma
{
	// -- Component Array
	struct IComponentArray
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

			Logger::getInstance()->Log("Registered Component!");

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
		T& GetData(Entity entity)
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
		// On App start you HAVE to call this function on every Component you have
		template <typename T> void RegisterComponent()
		{
			// Get String Pointer of type
			const char* _name = typeid(T).name();

			assert(m_RegisteredComponentTypes.find(_name) == m_RegisteredComponentTypes.end() && "Cannot register already registered Component");

			// Register Component Type
			m_RegisteredComponentTypes.insert(std::make_pair(_name, m_NextComponentType));

			// Create Component Array of given Component Type and insert it into the m_ComponentArrays Map
			m_ComponentArrays.insert(std::make_pair(_name, std::make_shared<ComponentArray<T>>()));

			// Increase next Component Type
			++m_NextComponentType;
		}

		// Returns the registered Type of the given Component
		template <typename T> ComponentType GetComponentType()
		{
			const char* _name = typeid(T).name();

			assert(m_RegisteredComponentTypes.find(_name) != m_RegisteredComponentTypes.end() && "Component not registered!");

			return m_RegisteredComponentTypes[_name];
		}

		// Adds a Component to an Entity
		template <typename T> void AddComponent(Entity entity, T component)
		{
			GetComponentArray<T>()->Insert(entity, component);
		}

		// Removes a Component from the Entity
		template <typename T> void RemoveComponent(Entity entity)
		{
			GetComponentArray<T>()->Remove(entity);
		}

		// Returns a Reference to 
		template <typename T> T& GetComponent(Entity entity)
		{
			GetComponentArray<T>()->GetData(entity);
		}

		// Notify each Component Array that an Entity has been destroyed
		// The Array will update its maps when it contains a Component of that Type
		void EntityDestroyed(Entity entity)
		{
			for (auto& const pair : m_ComponentArrays)
			{
				auto const& _component = pair.second;
				_component->EntityDestroyed(entity);
			}
		}

	private:
		// A Map that holds all registered Component Types by their String Pointer
		std::unordered_map<const char*, ComponentType> m_RegisteredComponentTypes{};

		// Map that holds all Component Arrays by their String Pointer
		std::unordered_map <const char*, std::shared_ptr<IComponentArray>> m_ComponentArrays{};

		// Component Type to be assigned to the next Component that gets registered
		ComponentType m_NextComponentType = 0;

		// Function that returns statically casted Pointer to the Component Array
		template <typename T> std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			const char* _name = typeid(T).name;

			assert(m_RegisteredComponentTypes.find(_name) != m_RegisteredComponentTypes.end() && "Component not registered!");

			return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[_name]);
		}
	};
}