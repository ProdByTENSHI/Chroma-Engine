#include "resources/Sprite.h"

#include "resources/ResourceManager.h"

namespace chroma
{
	Sprite::Sprite(const std::string& path)
	{
		LoadTexture(path);
	}

	Sprite::Sprite(SDL_Texture* texture)
	{
		m_Texture = texture;
	}

	Sprite::~Sprite()
	{
		delete m_Texture;
	}

	void Sprite::LoadTexture(const std::string& path)
	{
		m_Texture = ResourceManager::GetInstance()->GetTexture(path);
		m_Path = path;
	}
}