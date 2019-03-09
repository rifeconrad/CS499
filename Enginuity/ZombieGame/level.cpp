#include "level.h"

#include <SPEngine2D/eng_errors.h>
#include <SPEngine2D/resource_manager.h>

#include <fstream>

#include <iostream>

Level::Level(const std::string & filename)
{
	std::ifstream file(filename.c_str());

	if (file.fail())
	{
		SPEngine2D::FatalError("Failed to open " + filename);
	}

	std::string temp = "";
	// extract the "Humans:" and ignore it, then extra the number associated with it for storage
	file >> temp >> this->num_humans;

	// read in the level data
	while (std::getline(file, temp))
	{
		this->level_data.push_back(temp);
	}
	
	this->sprite_batch.begin();

	glm::vec4 uvRect(0.f, 0.f, 1.f, 1.f);
	SPEngine2D::Color white;
	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 255;

	// begin assigning tiles
	for (int row = 0; row < this->level_data.size(); row++)
	{
		for (int col = 0; col < this->level_data[row].size(); col++)
		{
			// identify the tile
			char tile = this->level_data[row][col];

			// get the destination rectangle
			glm::vec4 destRect(col * TILE_WIDTH, row * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			switch (tile)
			{
			case 'B':
			case 'R':
				this->sprite_batch.draw(destRect, 
					uvRect, 
					SPEngine2D::ResourceManager::getTexture("textures/red_bricks.png").id,
					0.f,
					white);
				break;
			case 'G':
				this->sprite_batch.draw(destRect,
					uvRect,
					SPEngine2D::ResourceManager::getTexture("textures/glass.png").id,
					0.f,
					white);
				break;
			case 'L':
				this->sprite_batch.draw(destRect,
					uvRect,
					SPEngine2D::ResourceManager::getTexture("textures/light_bricks.png").id,
					0.f,
					white);
				break;
			case '@':
				this->player_starting_pos.x = col * TILE_WIDTH;
				this->player_starting_pos.y = row * TILE_WIDTH;
				break;
			case 'Z':
				this->zombie_starting_pos.emplace_back(col * TILE_WIDTH, row * TILE_WIDTH);
				break;
			case '.':
				break;
			default:
				std::cerr << "Unexpected tile symbol: " << tile << "\n";
				break;
			};
		}
	}

	this->sprite_batch.end();
}

Level::~Level()
{
}

void Level::draw()
{
	this->sprite_batch.renderBatch();
}
