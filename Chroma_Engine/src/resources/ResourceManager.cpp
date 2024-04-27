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
}