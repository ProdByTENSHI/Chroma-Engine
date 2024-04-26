#pragma once

#include <glm.hpp>

namespace chroma
{
	struct TransformComponent
	{
		TransformComponent() { position = glm::vec3(0, 0, 0); }
		TransformComponent(glm::vec3 position) : position(position) {}

		glm::vec3 position;
	};
}