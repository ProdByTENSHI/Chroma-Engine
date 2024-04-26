#pragma once

#include "resources/Sprite.h"
#include "ecs/Components/Components.h"
#include "ecs/ECS_Definitions.h"
#include "ecs/ECS.h"

namespace chroma
{
	// -- Component
	struct SpriteComponent
	{
		SpriteComponent() : m_Sprite(nullptr) {}
		SpriteComponent(Sprite* sprite) : m_Sprite(sprite) {}
		SpriteComponent(const std::string& path) : m_Sprite(nullptr)
		{
			m_Sprite = new Sprite(path);
		}

		Sprite* m_Sprite;
	};
}