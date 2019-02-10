#pragma once

#include "sprite.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "GLSL_program.h"

enum class EngineState {PLAY = 0, EXIT};
class MainEngine
{
public:
	MainEngine();
	~MainEngine();

	void run();

private:
	SDL_Window* window;

	int screen_width;
	int screen_height;

	EngineState current_state;

	void init();
	void initShaders();
	void handleInput();
	void draw();
	void engineLoop();

	Sprite sprite;

	GLSLProgram color_program;
};

