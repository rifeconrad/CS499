#pragma once

#include <map>
#include <string>

#include "GLTexture.h"

namespace SPEngine2D
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texture_path);

	private:
		std::map<std::string, GLTexture> texture_map;
	};

}