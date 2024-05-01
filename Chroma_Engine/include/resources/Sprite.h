#pragma once

#include <string>

namespace chroma
{
	class Sprite
	{
	public:
		Sprite(const std::string& path);
		~Sprite();

	private:
		std::string m_Path;

	};
}