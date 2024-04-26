#pragma once

#include "ecs/ECS_Definitions.h"

#include <unordered_map>
#include <memory>
#include <assert.h>

namespace chroma
{
	// Handles everything ECS System related
	class SystemManager
	{
	public:
		// Puts a System into the Register and returns a Shared Pointer to it
		template <typename T> std::shared_ptr<T> RegisterSystem()
		{
			const char* _name = typeid(T).name();

			assert(m_Systems.find(_name) == m_Systems.end() && "System already registered!");

			auto _system = std::make_shared<T>();
			m_Systems.insert(std::make_pair(_name, _system));

			return _system;
		}

		// Sets the Signature of the given System
		template <typename T> void SetSignature(Signature signature)
		{
			const char* _name = typeid(T).name();

			assert(m_Systems.find(_name) != m_Systems.end() && "System not registered!");

			m_Signatures.insert(std::make_pair(_name, signature));
		}

		// Removes Entity from all Systems Entity m_Entities set
		void EntityDestroyed(Entity entity)
		{
			for (auto const& pair : m_Systems)
			{
				auto const& _system = pair.second;
				_system->m_Entities.erase(entity);
			}
		}

		// Removes the Entity from its old Systems and adds it into all Systems that have the same Signature
		void EntitySignatureChange(Entity entity, Signature signature)
		{
			for (auto const& pair : m_Systems)
			{
				auto const& _type = pair.first;
				auto const& _system = pair.second;
				auto const& _systemSignature = m_Signatures[_type];

				if ((signature & _systemSignature) == _systemSignature)
				{
					// Add to Systems Entity Set
					_system->m_Entities.insert(entity);
				}
				else
				{
					// Remove from Systems Entity Set
					_system->m_Entities.erase(entity);
				}
			}
		}

	private:
		// A Map that holds all System Signatures by their String Pointer
		std::unordered_map<const char*, Signature> m_Signatures;

		// A Map that holds all Systems as Shared Pointers by their String Pointer
		std::unordered_map <const char*, std::shared_ptr<System>> m_Systems;

	};
}