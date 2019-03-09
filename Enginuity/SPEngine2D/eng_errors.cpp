#include "eng_errors.h"

#include <cstdlib>

#include <iostream>
#include <SDL2/SDL.h>

namespace SPEngine2D
{
	void FatalError(std::string e_message)
	{
		std::cerr << e_message << "\n";
		std::cin.get();
		SDL_Quit(); // shut down SDL
		exit(1);    // close the game
	}
}