#pragma once

#include <string>

#include "texture_cache.h"

namespace SPEngine2D
{
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texture_path);

	private:
		static TextureCache texture_cache;
	};

}
