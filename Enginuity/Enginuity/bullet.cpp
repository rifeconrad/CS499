#include "bullet.h"

#include <SPEngine2D/GLTexture.h>
#include <SPEngine2D/resource_manager.h>

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float speed, int life_time)
{
	this->life_time = life_time;
	this->position = position;
	this->direction = direction;
	this->speed = speed;
}

Bullet::~Bullet()
{
}

void Bullet::draw(SPEngine2D::SpriteBatch& sprite_batch)
{
	glm::vec4 uv(0.f, 0.f, 1.f, 1.f);
	static SPEngine2D::GLTexture texture = SPEngine2D::ResourceManager::getTexture("textures/jimmy_jump_pack/PNG/Enemys/Enemy_Broccoli1.png");
	SPEngine2D::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 pos_and_size = glm::vec4(this->position.x, this->position.y, 30, 30);

	sprite_batch.draw(pos_and_size, uv, texture.id, 0.f, color);
}

bool Bullet::update()
{
	this->position += this->direction * this->speed;
	this->life_time--;

	if (life_time == 0)
		return true;

	return false;
}
