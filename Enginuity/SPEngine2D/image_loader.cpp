#include "image_loader.h"
#include "picopng.h"
#include "io_manager.h"
#include "eng_errors.h"

namespace SPEngine2D
{
	GLTexture ImageLoader::loadPNG(std::string file_path)
	{
		GLTexture texture = { 0 };

		//----------------------------------------
		// SEE picopng.h for any questions
		//----------------------------------------

		// input data
		std::vector<unsigned char> in;
		// output for the decode PNG (pixel data)
		std::vector<unsigned char> out;
		unsigned long width;
		unsigned long height;

		if (!IOManager::readFileToBuffer(file_path, in))
		{
			FatalError("Failed to load PNG file to buffer: " + file_path);
		}

		int error_check = decodePNG(out, width, height, &in[0], in.size());

		if (error_check != 0)
		{
			FatalError("decodePNG failed with error: " + std::to_string(error_check));
		}

		// generate the texture
		// 1 - # of textures
		// &(texture.id) - id of the texture (in this case, obtaining the id)
		glGenTextures(1, &(texture.id));

		// bind the texture
		glBindTexture(GL_TEXTURE_2D, texture.id);

		// upload the image data to the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		// tell openGL about the texture and how to treat the texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// What is mipmapping?
		// The process of filtering the pixels to prevent an excess of pixel data.
		// In other words, if an image is tiny, we don't care about all of the pixels within
		// we can combine some pixel data and the user will see what appears to be the same image.
		// Now, we can use less pixels and save more memory!
		glGenerateMipmap(GL_TEXTURE_2D);

		// unbind the texture
		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;


		return texture;
	}
}