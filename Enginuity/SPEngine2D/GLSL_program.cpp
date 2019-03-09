#include "GLSL_program.h"

#include "eng_errors.h"

#include <vector>
#include <fstream>
#include <iostream>

namespace SPEngine2D
{
	GLSLProgram::GLSLProgram() : programID(0), vertexID(0), fragmentID(0), num_attributes(0)
	{
	}

	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::CompileShaders(const std::string & vertex_path, const std::string & fragment_path)
	{
		// get program object
		this->programID = glCreateProgram();

		// create a vertex shader
		this->vertexID = glCreateShader(GL_VERTEX_SHADER);
		if (this->vertexID == 0)
		{
			FatalError("Vertex shader failed to be created\n");
		}

		// create a fragment shader
		this->fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		if (this->fragmentID == 0)
		{
			FatalError("Fragment shader failed to be created\n");
		}

		// compile shaders
		this->CompileShader(vertex_path, this->vertexID);
		this->CompileShader(fragment_path, this->fragmentID);
	}

	void GLSLProgram::LinkShaders()
	{
		// now that vertex and fragment shaders are successfully compiled...
		// link them together into a program

		// attach the shaders to our program
		glAttachShader(this->programID, this->vertexID);
		glAttachShader(this->programID, this->fragmentID);

		// link our program
		glLinkProgram(this->programID);

		// verify that everything was linked properly (compare to CompileShaders for more detail)
		GLint isLinked = 0;
		glGetProgramiv(this->programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint max_length = 0;
			glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &max_length);

			std::vector<char> error_log(max_length);
			glGetProgramInfoLog(this->programID, max_length, &max_length, &error_log[0]);

			// program failed, so delete it (otherwise, it will cause a leak)
			glDeleteProgram(this->programID);

			// shaders failed, so delete them (otherwise, it will cause a leak)
			glDeleteShader(this->vertexID);
			glDeleteShader(this->fragmentID);

			// print the link error we received
			std::printf("%s\n", &error_log[0]);
			FatalError("Shader failed to link");
		}

		// always detach shaders after a successful link
		glDetachShader(this->programID, this->vertexID);
		glDetachShader(this->programID, this->fragmentID);
		glDeleteShader(this->vertexID);
		glDeleteShader(this->fragmentID);
	}

	void GLSLProgram::addAttribute(const std::string & attribute_name)
	{
		// num_attributes - index to latest attribute from GLSL file (see colorShading.vert for commented description)
		glBindAttribLocation(this->programID, this->num_attributes++, attribute_name.c_str());
	}

	GLint GLSLProgram::getUniformLocation(const std::string & uniform_name)
	{
		GLint location = glGetUniformLocation(this->programID, uniform_name.c_str());

		if (location == GL_INVALID_INDEX)
		{
			FatalError("Uniform " + uniform_name + " not found in shader.\n");
		}

		return location;
	}

	void GLSLProgram::use()
	{
		// use the program we have created (w/ the shaders)
		glUseProgram(this->programID);

		// loop through each attribute and enable their use
		for (int i = 0; i < this->num_attributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse()
	{
		// stop using the program we had created
		glUseProgram(0);

		// loop through each attribute and disable their use
		for (int i = 0; i < this->num_attributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}

	void GLSLProgram::CompileShader(const const std::string& path, GLuint& ID)
	{

		// READING IN SHADER FILE
		std::ifstream file(path.c_str());
		if (file.fail())
		{
			perror(path.c_str());
			FatalError("Failed to open: " + path);
		}
		std::string file_contents;
		std::string line;
		while (std::getline(file, line))
		{
			file_contents += line + "\n";
		}
		file.close();
		// END READING IN SHADER FILE

		// 1 - # of strings w/ vertex file content within
		// contents - a pointer to the contents of our shader file
		// nullptr - strings are null terminated
		const char* contents = file_contents.c_str();
		glShaderSource(ID, 1, &contents, nullptr);
		glCompileShader(ID);

		// checks if the shader was successfully created
		GLint success = 0;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			// constructs an error log to explain any shader errors
			GLint max_length = 0;
			glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &max_length);

			if (max_length != 0)
			{
				// creates a string of size max length (which is defined by glGetShaderiv
				std::vector<GLchar> error_log(max_length);
				// gives use the errors associated with the vertex shader
				glGetShaderInfoLog(ID, max_length, &max_length, &error_log[0]);

				// print off the shader error received
				std::printf("%s\n", &error_log[0]);

				FatalError("Shader " + path + " failed to compile");
			}
			else
			{
				FatalError("Shader " + path + " failed to compile with unknown reason");
			}

		}
	}
}