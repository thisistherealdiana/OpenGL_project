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
#include "Shader.h"

class Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLint diffuseTex;
	GLint specularTex;
public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->diffuseTex = diffuseTex;
		this->specularTex = specularTex;

	}

	~Material(){}

	void sendToShader(Shader& program)
	{
		program.setVec3f(ambient, "material.ambient");
		program.setVec3f(diffuse, "material.diffuse");
		program.setVec3f(specular, "material.specular");
		program.set1i(diffuseTex, "material.diffuseTex");
		program.set1i(specularTex, "material.specularTex");

	}
};