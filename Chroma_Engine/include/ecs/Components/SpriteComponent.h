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
		Sprite* m_Sprite;
	};
}