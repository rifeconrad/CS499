#include "resource_manager.h"

namespace SPEngine2D
{
	TextureCache ResourceManager::texture_cache;

	GLTexture ResourceManager::getTexture(std::string texture_path)
	{
		return texture_cache.getTexture(texture_path);
	}
}
