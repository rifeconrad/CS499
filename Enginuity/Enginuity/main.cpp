#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/GLU.h>
#include <GL/GL.h>

#include "main_engine.h"

#include <iostream>

int main(int argc, char** argv)
{
	MainEngine engine;
	engine.run();

	return 0;
}