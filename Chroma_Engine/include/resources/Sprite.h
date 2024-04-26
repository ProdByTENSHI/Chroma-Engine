#pragma once

#include <string>
#include <SDL_image.h>

namespace chroma
{
	class Sprite
	{
	public:
		Sprite(const std::string& path);
		Sprite(SDL_Texture* tetxure);

		~Sprite();

		//! Loads a Texture from the ResourceManager
		void LoadTexture(const std::string& path);

		//! Returns the current Texture
		SDL_Texture* GetTexture()
		{
			return m_Texture;
		}

		//! Returns the Path of the current Texture
		const std::string& GetPath()
		{
			return m_Path;
		}

	private:
		std::string m_Path;
		SDL_Texture* m_Texture;
	};
}