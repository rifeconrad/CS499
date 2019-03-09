#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

// out - output
// vec3 - for rgb color (float array[3])
// vec4 - for rgba color (float array[4])
out vec4 color;

// a uniform variable is constant over an entire mesh?
uniform sampler2D mySampler;

void main()
{
	// texture obtains the color from the sampler
	// (2nd parameter) UV coordinates - coordinates of the texture (U -> x and V -> y)
	// vec4 because RGBA will be returned
	vec4 textureColor = texture(mySampler, fragmentUV);

	color = textureColor * fragmentColor;
	
	// set the color to the value given from the vertex shader
	color = fragmentColor * textureColor;
}