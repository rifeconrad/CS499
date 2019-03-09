#pragma once

#include <GL/glew.h>

#include <string>

namespace SPEngine2D
{

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void CompileShaders(const std::string& vertex_path, const std::string& fragment_path);
		void LinkShaders();

		void addAttribute(const std::string& attribute_name);

		GLint getUniformLocation(const std::string& uniform_name);

		void use();
		void unuse();

	private:
		GLuint programID;  // refers to entire program
		GLuint vertexID;   // refers to vertex shader
		GLuint fragmentID; // refers to fragment shader
		int num_attributes;

		void CompileShader(const std::string& path, GLuint& ID);
	};
}

