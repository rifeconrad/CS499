#pragma once

#include <GL/glew.h>

namespace SPEngine2D
{
	// three chars for red green blue and alpha
	struct Color
	{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	// two floats for two dimensions
	struct Position
	{
		float x;
		float y;
	};

	struct UV
	{
		float u;
		float v;
	};

	// want vertex struct to be a multiple of 4 bytes
	struct Vertex
	{

		Position position; // total of 8 bytes (4 bytes per float)

		Color color;

		UV uv; // texture coordinates

		// functions to not increase the size (in bytes) of a struct
		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			this->color.r = r;
			this->color.g = g;
			this->color.b = b;
			this->color.a = a;
		}

		void setPosition(float x, float y)
		{
			this->position.x = x;
			this->position.y = y;
		}

		// U and V (aka X and Y) act as normalized position values
		/*
		   How much of the image do we want to show?
		   1.0
			^
			|
			|    IMAGE
		  V |    HERE
			|
	(U, V)  |
	(0, 0)  ---------------> 1.0
				   U
		*/
		void setUV(float u, float v)
		{
			this->uv.u = u;
			this->uv.v = v;
		}
	};
}