#pragma once

namespace chroma
{
	struct Vector2
	{
		Vector2() : x(0), y(0) {}
		Vector2(float x, float y) { this->x = x; this->y = y; }

		float x;
		float y;
	};

	struct TransformComponent
	{
		TransformComponent() : position(Vector2(0, 0)), size(Vector2(100, 100)) {}
		TransformComponent(Vector2 position, Vector2 size) : position(position), size(size) {}

		Vector2 position;
		Vector2 size;
	};
}