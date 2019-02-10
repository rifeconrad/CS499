#include "eng_errors.h"

#include <iostream>
#include <SDL2/SDL.h>

void FatalError(std::string e_message)
{
	std::cerr << e_message << "\n";
	std::cin.get();
	SDL_Quit();
}