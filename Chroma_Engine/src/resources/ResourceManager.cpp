#include "resources/ResourceManager.h"

namespace chroma
{
	static ResourceManager* instance;

	ResourceManager* ResourceManager::GetInstance()
	{
		if (instance == nullptr)
			instance = new ResourceManager();

		return instance;
	}

	SDL_Texture* ResourceManager::GetTexture(const std::string& path)
	{
		if (m_TextureCache.find(path) != m_TextureCache.end())
		{
			return m_TextureCache[path];
		}
		else
		{
			SDL_Surface* _loadedSurface = IMG_Load(path.c_str());
			if (_loadedSurface == nullptr)
			{
				std::cerr << "Could not load Texture from Path " << path.c_str() << std::endl;
				return nullptr;
			}

			SDL_Texture* _texture = SDL_CreateTextureFromSurface(m_Renderer->GetRenderer(), _loadedSurface);
			m_TextureCache.insert(std::make_pair(path, _texture));

			SDL_FreeSurface(_loadedSurface);

			std::cout << "Loaded Texture" << std::endl;

			return _texture;
		}
	}
}