#include "main_game.h"

#include <SPEngine2D/SPEngine2D.h>
#include <SPEngine2D/timing.h>

#include <iostream>

MainGame::MainGame() : screen_width(1024), screen_height(768), game_state(GameState::PLAY)
{
}


MainGame::~MainGame()
{
	for (int i = 0; i < this->levels.size(); i++)
		delete this->levels[i];
}

void MainGame::run()
{
	this->initSystems();

	this->gameLoop();
}

void MainGame::initSystems()
{
	SPEngine2D::init();

	this->window.create("Zombie Game", this->screen_width, this->screen_height, 0);

	this->initShaders();

	// add level one to our series of levels
	this->levels.push_back(new Level("levels/level1.txt"));
}

void MainGame::initShaders()
{
	this->texture_program.CompileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	this->texture_program.addAttribute("vertexPosition");
	this->texture_program.addAttribute("vertexColor");
	this->texture_program.addAttribute("vertexUV");
	this->texture_program.LinkShaders();
}

void MainGame::gameLoop()
{
	SPEngine2D::FPSLimiter fps_limiter;
	fps_limiter.setMaxFPS(60);

	while (this->game_state == GameState::PLAY)
	{
		fps_limiter.begin();

		this->processInput();
		this->drawGame();

		fps_limiter.end();
	}
}

void MainGame::processInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			break;
		case SDL_KEYDOWN:
			this->input_manager.keyPressed(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			this->input_manager.keyReleased(event.key.keysym.sym);
			break;
		case SDL_MOUSEMOTION:
			this->input_manager.setMouseCoord(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			this->input_manager.keyPressed(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			this->input_manager.keyReleased(event.button.button);
			break;
		}
	}
}

void MainGame::drawGame()
{
	// set the base depth to 1.0
	glClearDepth(1.f);

	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw code here



	// swap out buffer!
	this->window.swapBuffer();
}
