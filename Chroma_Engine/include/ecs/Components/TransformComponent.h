#pragma once

#include <glm.hpp>

namespace chroma
{
	struct TransformComponent
	{
		TransformComponent() { position = glm::vec2(0, 0); size = glm::vec2(100, 100); }
		TransformComponent(glm::vec2 position, glm::vec2 size) : position(position), size(size) {}

		glm::vec2 position;
		glm::vec2 size;
	};
}