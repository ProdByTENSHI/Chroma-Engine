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
		static EntityManager* GetInstance();

		EntityManager();

		// -- Entity Lifetime
		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		// -- Signature
		void SetSignature(Entity entity, Signature signature);
		Signature GetSignature(Entity entity);

	private:
		/*
		* Gets filled with MAX_ENTITIES Amount of Entities at the Start
		* When creating an Entity an Entity is popped of the Front(FIFO
		* When Destroying an Entity it is returned to the Queue
		*/
		std::queue<Entity> m_AvaiableEntities;

		// An Array that holds all Signatures where the Index corresponds to the Entity
		std::array<Signature, MAX_ENTITIES> m_Signatures;

		// Keeps track of the amount of Entities in the Scene
		uint32_t m_EntitiesInScene;
	};
}