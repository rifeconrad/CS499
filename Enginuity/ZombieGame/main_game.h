#pragma once

#include <SPEngine2D/window.h>
#include <SPEngine2D/GLSL_program.h>
#include <SPEngine2D/input_manager.h>
#include <SPEngine2D/camera_2D.h>
#include <SPEngine2D/resource_manager.h>

#include "level.h"

enum class GameState {
	PLAY = 0,
	EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	// runs the game
	void run();

private:
	// initialize the core system
	void initSystems();

	// initalizes the shaders
	void initShaders();

	// main game loop
	void gameLoop();

	// handles input
	void processInput();

	// render game
	void drawGame();

	SPEngine2D::Window window;
	SPEngine2D::GLSLProgram texture_program;
	SPEngine2D::InputManager input_manager;
	SPEngine2D::Camera2D camera;

	std::vector<Level*> levels;

	GameState game_state;

	int screen_width;
	int screen_height;
};

