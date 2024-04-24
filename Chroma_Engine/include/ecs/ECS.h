#pragma once

#include "logger/Logger.h"

#include <array>
#include <queue>
#include <bitset>

namespace chroma
{
	// -- Entity
	using Entity = std::uint32_t;			// An Entity is just an ID
	const Entity MAX_ENTITIES = 5000;		// Maximum Entities per Scene

	// -- Component
	using ComponentType = std::uint8_t;			// Each Component has a unique 'ID' which gets used to represent a Bit in the Signature Bitfield
	const ComponentType MAX_COMPONENTS = 32;	// Max Components per Entity

	// -- Signature
	// To know what Components an Entity has and what Components a certain System cares about a Bitfield is used
	using Signature = std::bitset<MAX_COMPONENTS>;

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