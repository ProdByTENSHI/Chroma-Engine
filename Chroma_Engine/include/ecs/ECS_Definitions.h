#pragma once

#include <set>
#include <bitset>

namespace chroma
{
	// -- Entity
	using Entity = std::uint32_t;				// An Entity is just an ID
	const Entity MAX_ENTITIES = 5000;			// Maximum Entities per Scene -> Override this Value to your needs

	// -- Component
	using ComponentType = std::uint8_t;			// Each Component has a unique 'ID' which gets used to represent a Bit in the Signature Bitfield
	const ComponentType MAX_COMPONENTS = 32;	// Max Components per Entity

	// -- Signature
	// To know what Components an Entity has and what Components a certain System cares about a Bitfield is used
	using Signature = std::bitset<MAX_COMPONENTS>;

	// A system is any functionality that iterates upon a list of entities with a certain signature of components
	// Base class for all Systems
	struct System
	{
		std::set<Entity> m_Entities;
	};
}