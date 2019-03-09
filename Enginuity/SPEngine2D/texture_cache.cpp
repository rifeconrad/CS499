#include "texture_cache.h"

#include <iostream>

#include "image_loader.h"

namespace SPEngine2D
{
	TextureCache::TextureCache()
	{
	}

	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texture_path)
	{
		auto check = this->texture_map.find(texture_path);

		// if we did not find the texture, create it!
		if (check == this->texture_map.end())
		{
			// load in the texture
			GLTexture new_tex = ImageLoader::loadPNG(texture_path);

			// add the texture to the map
			this->texture_map.insert(make_pair(texture_path, new_tex));

			// Loaded Texture

			// return the texture
			return new_tex;
		}

		// Used Cached Texture
		return check->second;
	}
}