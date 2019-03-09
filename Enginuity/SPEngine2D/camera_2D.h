#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>


namespace SPEngine2D {

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screen_width, int screen_height);

		void update();

		glm::vec2 convertScreenToWorld(glm::vec2 screen_coord);

		void setPosition(const glm::vec2& position) { this->position = position; this->update_matrix_needed = true; }
		glm::vec2 getPosition() { return position; }

		void setScale(const float& scale) { this->scale = scale; this->update_matrix_needed = true; }
		float getScale() { return this->scale; }

		glm::mat4 getCameraMatrix() { return this->camera_matrix; }

	private:
		int screen_width;
		int screen_height;

		bool update_matrix_needed;

		// glm::vec2 is the same as a GLSL vec2
		glm::vec2 position; 
		glm::mat4 camera_matrix;

		glm::mat4 ortho_matrix;

		float scale;
	};

}