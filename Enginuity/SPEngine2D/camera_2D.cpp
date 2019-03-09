#include "camera_2D.h"

namespace SPEngine2D
{

	Camera2D::Camera2D() : position(0.f, 0.f), camera_matrix(1.f), scale(1.f), update_matrix_needed(true), screen_width(600), screen_height(600), ortho_matrix(1.f)
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int screen_width, int screen_height)
	{
		this->screen_width = screen_width;
		this->screen_height = screen_height;

		//         parameters reference the left-side, right-side, bottom, top of screen
		this->ortho_matrix = glm::ortho(0.f, (float)this->screen_width, 0.f, (float)this->screen_height);
	}

	void Camera2D::update()
	{
		if (this->update_matrix_needed)
		{
			// camera translation
			glm::vec3 translate(-this->position.x + this->screen_width / 2, -this->position.y + this->screen_height / 2, 0.f);
			this->camera_matrix = glm::translate(this->ortho_matrix, translate);

			// camera scale
			glm::vec3 scale(this->scale, this->scale, 0.f);
			this->camera_matrix = glm::scale(glm::mat4(1.f), scale) * this->camera_matrix;

			this->update_matrix_needed = false;
		}
	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screen_coord)
	{
		// invert y direction (because screen is flipped by default
		screen_coord.y = this->screen_height - screen_coord.y;

		// convert the coordinates so that 0,0 is in the center of the screen
		screen_coord -= glm::vec2(this->screen_width / 2, this->screen_height / 2);
		
		// scale the coordinates to allow for accurate distances (if scaled in, then the distances shown should be shorter and vice versa)
		screen_coord /= this->scale;

		// translate with the camera position
		screen_coord += this->position;

		return screen_coord;
	}

}