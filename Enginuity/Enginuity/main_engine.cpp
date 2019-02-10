#include "main_engine.h"

#include "eng_errors.h"

#include <iostream>
#include <string>

MainEngine::MainEngine() : window(nullptr), screen_width(1024), screen_height(768), current_state(EngineState::PLAY)
{
	this->window = nullptr;
	this->screen_width = 1024;
	this->screen_height = 768;
	this->current_state = EngineState::PLAY;
}

MainEngine::~MainEngine()
{
}

void MainEngine::init()
{
	// sets up SDL for us
	SDL_Init(SDL_INIT_EVERYTHING); 

	// create a window, specifically for opengl use
	this->window = SDL_CreateWindow("Enginuity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screen_width, this->screen_height, SDL_WINDOW_OPENGL);
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

	// sets up a double buffer for the window (prevents flickering of screen)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// set the background color of window
	glClearColor(0.f, 0.f, 1.f, 1.0);

	this->initShaders();
}

void MainEngine::initShaders()
{
	this->color_program.CompileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	this->color_program.addAttribute("vertexPosition");
	this->color_program.LinkShaders();
}

void MainEngine::run()
{
	init();

	sprite.init(-1.f, -1.f, 1.f, 1.f);

	engineLoop();
}

void MainEngine::engineLoop()
{
	while (this->current_state != EngineState::EXIT)
	{
		this->handleInput();
		this->draw();
	}
}

void MainEngine::handleInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			this->current_state = EngineState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cerr << event.motion.x << ", " << event.motion.y << "\n";
			break;
		}
	}
}

void MainEngine::draw()
{
	glClearDepth(1.0);
	// clear the color buffer and clear the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->color_program.use();

	sprite.draw();

	this->color_program.unuse();

	// adds everything drawn to non-shown window to the screen
	SDL_GL_SwapWindow(this->window);
}
