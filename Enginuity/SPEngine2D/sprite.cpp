#include "sprite.h"

#include "vertex.h"
#include "resource_manager.h"

#include <cstddef>

namespace SPEngine2D
{
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

	void Sprite::init(float x, float y, float width, float height, std::string texture_path)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;

		this->texture = ResourceManager::getTexture(texture_path);

		if (this->vbID == 0)
		{
			// generate a buffer and obtain the vertex buffer ID
			glGenBuffers(1, &vbID);
		}

		//          6 vertices * 2 (x and y point per vertex)
		Vertex vertex_data[6];

		// BUILD SQUARE (w/ SIX vertices)
		// VERTICES AND UVsFOR FIRST TRIANGLE
		vertex_data[0].setPosition(x + width, y + height);   // top right x and y
		vertex_data[0].setUV(1.0f, 1.0f);

		vertex_data[1].setPosition(x, y + height);           // top left x and y
		vertex_data[1].setUV(0.0f, 1.0f);

		vertex_data[2].setPosition(x, y);                    // bottom left x and y
		vertex_data[2].setUV(0.0f, 0.0f);
		// END OF VERTICES FOR FIRST TRIANGLE

		// VERTICES AND UVs FOR SECOND TRIANGLE
		vertex_data[3].setPosition(x, y);                    // bottom left x and y
		vertex_data[3].setUV(0.0f, 0.0f);

		vertex_data[4].setPosition(x + width, y);            // bottom right x and y
		vertex_data[4].setUV(1.0f, 0.0f);

		vertex_data[5].setPosition(x + width, y + height);   // top right x and y
		vertex_data[5].setUV(1.0f, 1.0f);
		// END OF VERTICES FOR SECOND TRIANGLE

		// SET VERTEX COLOR
		for (int i = 0; i < 6; i++)
			vertex_data[i].setColor(255, 0, 255, 255);

		vertex_data[1].setColor(0, 0, 255, 255);

		vertex_data[4].setColor(0, 255, 0, 255);
		// END SET COLOR

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

		// bind our texture
		// DO NOT UNBIND - it could interfere with other sprites using the same texture!
		glBindTexture(GL_TEXTURE_2D, this->texture.id);

		// make this vertex buffer active
		glBindBuffer(GL_ARRAY_BUFFER, this->vbID);

		// we only want one attribute array right now (position), later we can add more for lighting, etc.
		// 0 indicates the 0th position of the attribute array
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// this is the position attribute pointer!
		// tell opengl where our vertex data is in the vertex buffer ID
		// 0 - 0th position of array
		// 2 - (stands for x and y coordinate)
		// GL_FLOAT - tells it we will be using float
		// GL_FALSE - says we don't want to normalize
		// 0 - stride - size of the vertex struct
		// offsetof(...) - byte offset of struct (since position is at the beginning of the struct, this will return 0) 
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		// this is the color attribute pointer
		// 1 - color is the second index in our shader
		// 4 - the number of bytes involved
		// GL_UNSIGNED_BYTES - the data type is unsigned bytes
		// GL_TRUE - we want to normalize (for color, it converts our 0-255 to between 0 and 1)
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		// UV attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		// tell opengl to DRAW!
		// GL_TRIANGLES - mode we want to draw in (everything is triangles regardless, so make it triangles)
		// 0 - 0th element
		// 6 - six vertices were defined in Sprite::init, so this is saying that we want 6 vertices!
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// disable the attribute array after use
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// unbind buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::update()
	{
	}
}