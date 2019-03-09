#pragma once

#include <GLM/glm.hpp>

#include <unordered_map>

namespace SPEngine2D
{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void setMouseCoord(float x, float y);
		glm::vec2 getMouseCoord();

		void keyPressed(unsigned int key);
		void keyReleased(unsigned int key);

		bool isKeyPressed(unsigned int key);

	private:
		std::unordered_map<unsigned int, bool> keyMap;

		glm::vec2 mouse_coord;
	};

}