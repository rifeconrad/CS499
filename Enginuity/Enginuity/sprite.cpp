#include "sprite.h"



Sprite::Sprite()
{
	this->vbID = 0;
}

Sprite::~Sprite()
{
	if (this->vbID != 0)
	{
		// tell opengl that we don't need the buffer anymore
		glDeleteBuffers(1, &this->vbID);
	}
}

void Sprite::init(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	if (this->vbID == 0)
	{
		// generate a buffer and obtain the vertex buffer ID
		glGenBuffers(1, &vbID);
	}

	//          6 vertices * 2 (x and y point per vertex)
	float vertex_data[12];

	// BUILD SQUARE (w/ SIX vertices)
	// VERTICES FOR FIRST TRIANGLE
	vertex_data[0] = x + width;   // top right x
	vertex_data[1] = y + height;  // top right y
	
	vertex_data[2] = x;           // top left x
	vertex_data[3] = y + height;  // top left y

	vertex_data[4] = x;           // bottom left x
	vertex_data[5] = y;           // bottom left y
	// END OF VERTICES FOR FIRST TRIANGLE

	// VERTICES FOR SECOND TRIANGLE
	vertex_data[6] = x;           // bottom left x
	vertex_data[7] = y;           // bottom left y

	vertex_data[8] = x + width;   // bottom right x
	vertex_data[9] = y;           // bottom right y

	vertex_data[10] = x + width;  // top right x
	vertex_data[11] = y + height; // top right y
	// END OF VERTICES FOR SECOND TRIANGLE
	// END BUILD SQUARE

	// have opengl make the buffer active and prepare for an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->vbID);
	// upload buffer data (we are uploading an array, the size of the array, a pointer to the first position of the array, draw it once - for now)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
	// unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	// make this vertex buffer active
	glBindBuffer(GL_ARRAY_BUFFER, this->vbID);

	// we only want one attribute array right now (position), later we can add more for lighting, etc.
	// 0 indicates the 0th position of the attribute array
	glEnableVertexAttribArray(0);

	// tell opengl where our vertex data is in the vertex buffer ID
	// 0 - 0th position of array
	// 2 - (stands for x and y coordinate)
	// GL_FLOAT - tells it we will be using float
	// GL_FALSE - says we don't want to normalize
	// 0 - stride?
	// 0 - unneccessary at the moment
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// tell opengl to DRAW!
	// GL_TRIANGLES - mode we want to draw in (everything is triangles regardless, so make it triangles)
	// 0 - 0th element
	// 6 - six vertices were defined in Sprite::init, so this is saying that we want 6 vertices!
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// disable the attribute array after use
	glDisableVertexAttribArray(0);

	// unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::update()
{
}
