#include "SPEngine2D.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace SPEngine2D
{
	int init()
	{
		// sets up SDL for us
		SDL_Init(SDL_INIT_EVERYTHING);

		// sets up a double buffer for the window (prevents flickering of screen)
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}