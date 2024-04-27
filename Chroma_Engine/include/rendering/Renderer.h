#pragma once

#include <SDL.h>
#include <bgfx/bgfx.h>

namespace chroma
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		bool GetCreationStatus() const
		{
			return m_CreationStatus;
		}

	private:
		bool m_CreationStatus;
	};
}