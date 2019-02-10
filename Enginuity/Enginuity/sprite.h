#pragma once

#include <GL/glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height);
	

	void draw();
	void update();

private:
	float x;
	float y;
	float width;
	float height;

	// vertex buffer ID - similar to a file descriptor, where it is a unique id given to the vertex buffer for easy access
	GLuint vbID; // GLuint is an unsigned int that is guaranteed to be 32-bits
};

