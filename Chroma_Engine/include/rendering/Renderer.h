#pragma once

#include <SDL.h>

namespace chroma
{
	class Renderer
	{
	public:
		Renderer();

		inline bool GetCreationStatus() const
		{
			return m_CreationStatus;
		}

	private:
		bool m_CreationStatus;
	};
}