#include "io_manager.h"

#include <fstream>

namespace SPEngine2D
{
	bool IOManager::readFileToBuffer(std::string & file_path, std::vector<unsigned char>& buffer)
	{
		// STACK OVERFLOW COMMENT
		// "ios::binary makes sure the data is read or written without translating 
		// new line characters to and from \r\n on the fly. In other words, exactly
		// what you give the stream is exactly what's written."
		std::ifstream file(file_path.c_str(), std::ios::binary);

		// check if opening the file was successful
		if (file.fail())
		{
			perror(file_path.c_str());
			return false;
		}

		// start from the end of the file (seekg moves the "cursor" to the end of the file)
		// this will help us obtain the file size!
		file.seekg(0, std::ios::end);

		// get the file size (tellg returns the number of bytes)
		int file_size = file.tellg();

		// now, move the "cursor" to the beginning of the file, so we can read the contents
		file.seekg(0, std::ios::beg);

		// there is a file header at the beginning of a file we want to ignore the bytes of
		// (when a file is stored, the header is ignored!)
		file_size -= file.tellg(); // probably not necessary

		// resize the buffer to the file size
		// (caution: this creates unallocated slots)
		buffer.resize(file_size);

		// read the file into our buffer
		// ((char*)&buffer[0] gives us a unsigned char* to the first element of the buffer,
		// and we want to convert it to a char* to fulfill parameter obligations)
		// In other words, a vector is actually hidden T*
		file.read((char*)&buffer[0], file_size);

		// close the file
		file.close();

		return true;
	}
}