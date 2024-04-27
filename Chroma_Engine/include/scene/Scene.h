#pragma once

#include "ecs/ECS.h"
#include "ecs/ECS_Definitions.h"

namespace chroma
{
	// -- Data to Save
	//		- Entities with their Components
	//		- Component Data

	struct SceneData
	{
	};

	//! A Scene is a State of a Game that stores Entities with their Components and their Data
	class Scene
	{
	public:
		//! Overrides the m_Data Struct
		void Save();

		//! Loads the given Data into this Scene
		void Load(const SceneData& data);

	private:
		SceneData m_Data;

	};

	// TODO: Write and Read Scene Data
	// TODO: Load Scene from Data
}