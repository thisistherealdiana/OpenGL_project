#pragma once
#include <glad/glad.h> 
#include <gl/GL.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <vec2.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "stb_image.h"

class Shader
{
private:
	GLuint id;	//program id

	std::string loadShaderSource(const char* fileName) 
	{
		std::string temp = "";
		std::string source = "";

		std::fstream in_file;

		in_file.open(fileName);

		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
			{
				source = source + temp + "\n";
			}
		}
		else
		{
			std::cout << "SHADER: Can't Open File: " << fileName << std::endl;
		}

		in_file.close();

		return source;
	}

	GLuint loadShader(GLenum type, const char* fileName)
	{
		char infolog[512]; // for error messages
		GLint success;

		GLuint shader = glCreateShader(type); // to create Shader ID
		std::string string_source = this->loadShaderSource(fileName);
		const GLchar* source = string_source.c_str();
		glShaderSource(shader, 1, &source, NULL); // to set the source to the just created shader
		glCompileShader(shader); // to compile our shader 

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infolog);
			std::cout << "SHADER: Can't Compile Shader: " << fileName << std::endl << infolog << std::endl;
		}

		return shader;
	}

	void linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader)	
	{
		char infolog[512]; // for error messages
		GLint success;

		this->id = glCreateProgram();

		glAttachShader(this->id, vertexShader);
		glAttachShader(this->id, fragmentShader);
		if (geometryShader) 
			glAttachShader(this->id, geometryShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infolog);
			std::cout << "SHADER: Can't Link the Program" << std::endl << infolog << std::endl;
		}

		glUseProgram(0); // to reset the program we are currently using
	}

public:
	// Constructor
	Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile = "")
	{
		GLuint vertexShader = 0;
		GLuint fragmentShader = 0;
		GLuint geometryShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);
		if (geometryFile != "")
			geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);

		this->linkProgram(vertexShader, fragmentShader, geometryShader);

		//End
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteShader(geometryShader);
	}

	// Destructor
	~Shader()
	{
		glDeleteProgram(id);
	}

	void use()
	{
		glUseProgram(id);
	}

	void unuse()
	{
		glUseProgram(0);
	}

	void setVec1f(GLfloat value, const GLchar* name)
	{
		use();
		glUniform1f(glGetUniformLocation(id, name), value);
		unuse();
	}

	void setVec2f(glm::fvec2 value, const GLchar* name)
	{
		use();
		glUniform2fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
		unuse();
	}

	void setVec3f(glm::fvec3 value, const GLchar* name)
	{
		use();
		glUniform3fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
		unuse();
	}

	void setVec4f(glm::fvec4 value, const GLchar* name)
	{
		use();
		glUniform4fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
		unuse();
	}

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		use();
		glUniformMatrix3fv(glGetUniformLocation(id, name), 1, transpose, glm::value_ptr(value));
		unuse();
	}

	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		use();
		glUniformMatrix4fv(glGetUniformLocation(id, name), 1, transpose, glm::value_ptr(value));
		unuse();
	}

	void set1i(GLint value, const GLchar* name)
	{
		use();
		glUniform1i(glGetUniformLocation(id, name), value);
		unuse();
	}
};