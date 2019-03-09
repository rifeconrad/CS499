#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <string>

namespace SPEngine2D
{
	// 0x1, 0x2, and 0x4 allow for the bitwise operator
	// INVISIBLE  -> hide the window
	// FULLSCREEN -> makes the screen a full screen
	// BORDERLESS -> makes the screen borderless
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		// possible enum error code later for clear error handling
		int create(std::string, int width, int height, unsigned int add_flags);

		void swapBuffer();

		inline int getWidth() { return width; }
		inline int getHeight() { return height; }

	private:
		SDL_Window* window;
		int width;
		int height;
	};

}