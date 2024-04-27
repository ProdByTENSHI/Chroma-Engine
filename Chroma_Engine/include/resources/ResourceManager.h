#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <SDL.h>
#include <SDL_image.h>

#include "rendering/Renderer.h"

namespace chroma
{
	class ResourceManager
	{
	public:
		// -- Singleton
		static ResourceManager* GetInstance();

		void Init(Renderer* renderer)
		{
			m_Renderer = renderer;
		}

	private:
		Renderer* m_Renderer;
	};
}