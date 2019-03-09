#pragma once

#include <vector>

namespace SPEngine2D
{
	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string& file_path, std::vector<unsigned char>& buffer);
	};
}

