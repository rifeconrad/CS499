#include "window.h"

#include "eng_errors.h"

namespace SPEngine2D
{
	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string window_name, int width, int height, unsigned int add_flags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		// did the user pass in INVISIBLE as a flag?
		if (add_flags & INVISIBLE)
			flags |= SDL_WINDOW_HIDDEN;

		if (add_flags & FULLSCREEN)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		if (add_flags |= BORDERLESS)
			flags |= SDL_WINDOW_BORDERLESS;

		// create a window, specifically for opengl use
		this->window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (this->window == nullptr)
		{
			FatalError("SDL Window could not be created\n");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(this->window);
		if (glContext == nullptr)
		{
			FatalError("SDL GL Context could not be created\n");
		}

		// sets up all extensions
		GLenum glew_check = glewInit();
		if (glew_check != GLEW_OK)
		{
			FatalError("Could not initialize glew\n");
		}

		// display the version of OpenGL used
		std::printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

		// set the background color of window
		glClearColor(0.f, 0.f, 1.f, 1.0);

		// turn on VSYNC
		SDL_GL_SetSwapInterval(1);

		// enable alpha blending (i.e. make png backgrounds transparent)
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(this->window);
	}
}