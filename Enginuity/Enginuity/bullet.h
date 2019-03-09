#pragma once

#include <GLM/glm.hpp>

#include <SPEngine2D/sprite_batch.h>

class Bullet
{
public:
	Bullet(glm::vec2 position, glm::vec2 direction, float speed, int life_time);
	~Bullet();

	void draw(SPEngine2D::SpriteBatch& sprite_batch);

	// return true when dead
	bool update();

private:
	int life_time;
	float speed;
	glm::vec2 direction;
	glm::vec2 position;

};

