#include "main_engine.h"

#include "SPEngine2D/eng_errors.h"
#include "SPEngine2D/SPEngine2D.h"
#include "SPEngine2D/resource_manager.h"

#include <GLM/glm.hpp>

#include <iostream>
#include <string>

MainEngine::MainEngine() : screen_width(1024), screen_height(768), current_state(EngineState::PLAY), time(0), MAX_FPS(60.f)
{
	camera.init(this->screen_width, this->screen_height);
}

MainEngine::~MainEngine()
{
}

void MainEngine::init()
{
	SPEngine2D::init();

	this->window.create("OpenGL Test One", screen_width, screen_height, 0);

	this->initShaders();

	this->sprite_batch.init();

	this->fps_limiter.init(this->MAX_FPS);
}

void MainEngine::initShaders()
{
	this->color_program.CompileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	this->color_program.addAttribute("vertexPosition");
	this->color_program.addAttribute("vertexColor");
	this->color_program.addAttribute("vertexUV");
	this->color_program.LinkShaders();
}

void MainEngine::run()
{
	this->init();

	

	this->engineLoop();
}

void MainEngine::engineLoop()
{
	while (this->current_state != EngineState::EXIT)
	{
		// used for frame time measuring
		this->fps_limiter.begin();

		this->handleInput();

		this->time += 0.1;

		this->camera.update();

		for (int i = 0; i < this->bullets.size();)
		{
			if (this->bullets[i].update())
			{
				this->bullets[i] = this->bullets.back();
				this->bullets.pop_back();
			}
			else
				i++;
		}

		this->draw();

		this->fps_limiter.end();
	}
}

void MainEngine::handleInput()
{
	SDL_Event event;

	const float camera_speed = 1.f;
	const float scale_speed = 0.1f;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			this->current_state = EngineState::EXIT;
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

	if (this->input_manager.isKeyPressed(SDLK_w))
		this->camera.setPosition(this->camera.getPosition() + glm::vec2(0.f, camera_speed));
	if (this->input_manager.isKeyPressed(SDLK_s))
		this->camera.setPosition(this->camera.getPosition() + glm::vec2(0.f, -camera_speed));
	if (this->input_manager.isKeyPressed(SDLK_a))
		this->camera.setPosition(this->camera.getPosition() + glm::vec2(-camera_speed, 0.f));
	if (this->input_manager.isKeyPressed(SDLK_d))
		this->camera.setPosition(this->camera.getPosition() + glm::vec2(camera_speed, 0.f));
	if (this->input_manager.isKeyPressed(SDLK_q))
		this->camera.setScale(this->camera.getScale() + scale_speed);
	if (this->input_manager.isKeyPressed(SDLK_e))
		this->camera.setScale(this->camera.getScale() - scale_speed);
	if (this->input_manager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouse_coord = this->input_manager.getMouseCoord();
		mouse_coord = this->camera.convertScreenToWorld(mouse_coord);
		
		glm::vec2 player_pos(0.f);
		glm::vec2 direction_from_player = mouse_coord - player_pos;
		direction_from_player = glm::normalize(direction_from_player);

		this->bullets.emplace_back(player_pos, direction_from_player, 5.f, 1000);
	}
}

void MainEngine::draw()
{
	glClearDepth(1.0);
	// clear the color buffer and clear the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->color_program.use();

	// glActiveTexture allows us to render multiple textures
	// GL_TEXTURE0 would be our first texture, then
	// GL_TEXTURE1 would be our second, etc.
	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = this->color_program.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0); // 0 references GL_TEXTURE0

	// set camera matrix
	GLuint pLocation = this->color_program.getUniformLocation("p");
	glm::mat4 camera_matrix = this->camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(camera_matrix[0][0]));

	this->sprite_batch.begin();

	//            x,   y,   w,    h
	glm::vec4 pos(0.f, 0.f, 50.f, 50.f);
	glm::vec4 uv(0.f, 0.f, 1.f, 1.f);
	static SPEngine2D::GLTexture texture = SPEngine2D::ResourceManager::getTexture("textures/jimmy_jump_pack/PNG/Enemys/Enemy_Broccoli1.png");
	SPEngine2D::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	this->sprite_batch.draw(pos, uv, texture.id, 0.f, color);

	for (int i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].draw(this->sprite_batch);
	}

	this->sprite_batch.end();
	this->sprite_batch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	this->color_program.unuse();

	// adds everything drawn to non-shown window to the screen
	this->window.swapBuffer();
}