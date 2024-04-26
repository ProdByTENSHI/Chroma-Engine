#pragma once

#include "ecs/ECS.h"
#include "ecs/ECS_Definitions.h"
#include "ecs/Components/TransformComponent.h"
#include "ecs/Components/SpriteComponent.h"

#include <rendering/Renderer.h>

namespace chroma
{
	struct SpriteRendererSystem : System
	{
		void Update(Renderer* renderer)
		{
			for (auto const& entity : m_Entities)
			{
				auto& _transformComponent = ECS::GetInstance()->GetComponent<TransformComponent>(entity);
				auto& _spriteComponent = ECS::GetInstance()->GetComponent<SpriteComponent>(entity);

				SDL_Rect _transform;
				_transform.w = _transformComponent.size.x;
				_transform.h = _transformComponent.size.y;
				_transform.x = _transformComponent.position.x;
				_transform.y = _transformComponent.position.y;

				renderer->RenderTexture(_spriteComponent.m_Sprite->GetTexture(), NULL, &_transform);
			}
		}
	};
}