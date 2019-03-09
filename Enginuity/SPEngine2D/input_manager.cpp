#include "input_manager.h"

namespace SPEngine2D
{

	InputManager::InputManager() : mouse_coord(0.f)
	{
	}

	InputManager::~InputManager()
	{
	}

	void InputManager::setMouseCoord(float x, float y)
	{
		this->mouse_coord.x = x;
		this->mouse_coord.y = y;
	}

	glm::vec2 InputManager::getMouseCoord()
	{
		return this->mouse_coord;
	}

	void InputManager::keyPressed(unsigned int key)
	{
		this->keyMap[key] = true;
	}

	void InputManager::keyReleased(unsigned int key)
	{
		this->keyMap[key] = false;
	}

	bool InputManager::isKeyPressed(unsigned int key)
	{
		auto it = this->keyMap.find(key);
		if (it != this->keyMap.end())
			return it->second;

		return false;
	}

}