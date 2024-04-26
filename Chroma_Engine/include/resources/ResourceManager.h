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

		// -- Resource Management
		//! Returns a Texture either from the Cache or the Disk
		SDL_Texture* GetTexture(const std::string& path);

	private:
		Renderer* m_Renderer;

		std::unordered_map<std::string, SDL_Texture*> m_TextureCache;
	};
}