#version 130

// input data from the vertex buffer for position (float array[2])
in vec2 vertexPosition;

// input data from the vertex buffer for color (float array[4])
in vec4 vertexColor;

in vec2 vertexUV;

out vec2 fragmentPosition;
// this will pass our color defined here to the fragment shader
// compare to colorShading.frag "vec4 fragmentColor"
out vec4 fragmentColor;

out vec2 fragmentUV;

// adding the "flat" key word prior to "out vec4 fragmentColor" would ignore interpolation between vertices
// to do this, the "flat" key word would have to be placed before the in statement in the frag file also!

// camera
uniform mat4 p;

void main()
{
	// set the x,y position on the screen
	// convert vertex position to vec4 (so it can be multiplied to the mat4) and pull out the x and y coordinates
	gl_Position.xy = (p * vec4(vertexPosition, 0.0, 1.0)).xy;
	
	// the z position is zero, since we are in 2D
	gl_Position.z = 0.0; 
	
	// indicate thet the coordinates are normalized
	gl_Position.w = 1.0; 
	
	fragmentPosition = vertexPosition;
	
	// set our fragmentColor, which will be passed to colorShading.frag
	fragmentColor = vertexColor;
	
	//            flips the vertex right-side up
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}