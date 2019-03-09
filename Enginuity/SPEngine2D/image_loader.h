#pragma once

#include "GLTexture.h"

#include <string>

namespace SPEngine2D
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string file_path);
	};
}

