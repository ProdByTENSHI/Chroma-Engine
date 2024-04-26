#pragma once

#include "ecs/EntityManager.h"
#include "ecs/ComponentManager.h"
#include "ecs/SystemManager.h"

namespace chroma
{
	//! Centralizes ECS Management into one Class for convenience
	class ECS
	{
	public:
		// -- Singleton

		static ECS* GetInstance();

		//! Call this before using the ECS as this creates the Initialize
		void Init();

		// -- Entity Management
		//! Creates a new Entity and returns it
		Entity CreateEntity();

		//! Destroys an Entity and notifies all Managers about it
		void DestroyEntity(Entity entity);

		// -- Component Management
		//! Wrapper for the RegisterComponent Function from the ComponentManager
		template <typename T> void RegisterComponent()
		{
			m_ComponentManager->RegisterComponent<T>();
		}

		//! Adds a Component to an Entity
		//! Make sure the Component has a default Constructor or else you will get an deleted function error!
		template <typename T> void AddComponent(Entity entity, T component)
		{
			m_ComponentManager->AddComponent(entity, component);

			std::cout << "Added Component to Entity " << entity << std::endl;

			// Set Signature to Component Type
			Signature _signature = m_EntityManager->GetSignature(entity);
			_signature.set(m_ComponentManager->GetComponentType<T>(), true);

			// Set Signature in Managers
			m_EntityManager->SetSignature(entity, _signature);
			m_SystemManager->EntitySignatureChange(entity, _signature);
		}

		//! Removes a Component from an Entity
		template <typename T> void RemoveComponent(Entity entity, T component)
		{
			m_ComponentManager->RemoveComponent(entity, component);

			// Set Signature to Component Type
			Signature _signature = m_EntityManager->GetSignature();
			_signature.set(m_ComponentManager->GetComponentType<T>(), false);

			// Set Signature in Managers
			m_EntityManager->SetSignature(entity, _signature);
			m_SystemManager->EntitySignatureChange(entity, _signature);
		}

		//! Returns a Reference to a Component of an Entity
		template <typename T> T& GetComponent(Entity entity)
		{
			return m_ComponentManager->GetComponent<T>(entity);
		}

		//! Returns the Component Type of T
		template <typename T> ComponentType GetComponentType()
		{
			return m_ComponentManager->GetComponentType<T>();
		}

		// -- System
		//! Registers the given System
		template <typename T> std::shared_ptr<T> RegisterSystem()
		{
			return m_SystemManager->RegisterSystem<T>();
		}

		//! Sets the Signature for the given System T
		template <typename T> void SetSystemSignature(Signature signature)
		{
			m_SystemManager->SetSignature<T>(signature);
		}

	private:
		// -- Manager
		EntityManager* m_EntityManager;
		ComponentManager* m_ComponentManager;
		SystemManager* m_SystemManager;
	};
}