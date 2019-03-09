#pragma once

#include <SPEngine2D/sprite_batch.h>

#include <GLM/glm.hpp>

#include <vector>
#include <string>

const int TILE_WIDTH = 64;

class Level
{
public:
	// load the level
	Level(const std::string& filename);
	~Level();

	void draw();

private:
	std::vector<std::string> level_data;
	int num_humans;

	SPEngine2D::SpriteBatch sprite_batch;

	glm::ivec2 player_starting_pos;
	std::vector<glm::ivec2> zombie_starting_pos;
};

