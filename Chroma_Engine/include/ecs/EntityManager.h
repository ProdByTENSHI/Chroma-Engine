#pragma once

#include "ecs/ECS_Definitions.h"
#include "logger/Logger.h"

#include <array>
#include <queue>

namespace chroma
{
	// -- Entity Manager
	class EntityManager
	{
	public:
		EntityManager();

		// -- Entity Lifetime
		//! Creates a new Entity
		Entity CreateEntity();

		//! Destroys the given Entity
		void DestroyEntity(Entity entity);

		// -- Signature
		//! Sets the Signature of the given Entity
		void SetSignature(Entity entity, Signature signature);

		//! Returns the Signature of the given Entity
		Signature GetSignature(Entity entity);

	private:
		/**
		* @brief Gets filled with MAX_ENTITIES Amount of Entities at the Start
		* When creating an Entity an Entity is popped of the Front(FIFO)
		* When Destroying an Entity it is returned to the Queue
		*/
		std::queue<Entity> m_AvaiableEntities;

		//! An Array that holds all Signatures where the Index corresponds to the Entity ID
		std::array<Signature, MAX_ENTITIES> m_Signatures;

		//! Keeps track of the amount of Entities in the Scene
		uint32_t m_EntitiesInScene;
	};
}