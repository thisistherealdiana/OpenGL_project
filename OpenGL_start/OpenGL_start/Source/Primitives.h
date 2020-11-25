#pragma once
#include <glad/glad.h> 
#include <gl/GL.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vertex.h"

class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	Primitive(){}

	virtual ~Primitive(){}

	// Functions
	void set(const Vertex* vertices, const unsigned numOfVertices, const GLuint* indices, const unsigned numOfIndices)
	{
		for (size_t i = 0; i < numOfVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}

		for (size_t i = 0; i < numOfIndices; i++)
		{
			this->indices.push_back(indices[i]);
		}
	}

	Vertex* getVertices()
	{
		return vertices.data();
	}

	GLuint* getIndices()
	{
		return indices.data();
	}

	const unsigned getNumOfVertices()
	{
		return vertices.size();
	}

	const unsigned getNumOfIndices()
	{
		return indices.size();
	}
};

class Quad : public Primitive
{
public:
	Quad() : Primitive()
	{
		Vertex vertices[] =
		{
			// Position                     // Color                        // Texture Coordinates  // Normals
			glm::vec3(-0.5f, 0.5f, 0.0f),   glm::vec3(1.0f, 0.0f, 0.0f),    glm::vec2(0.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(-0.5f,-0.5f, 0.0f),   glm::vec3(0.0f, 1.0f, 0.0f),    glm::vec2(0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f, -0.5f, 0.0f),   glm::vec3(0.0f, 0.0f, 1.0f),    glm::vec2(1.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f,  0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 0.0f),    glm::vec2(1.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f)
		};

		unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			//3, 2, 0,     // 3 points
			//2, 1, 0
			0,1,2,
			0,2,3
		};

		unsigned numOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, numOfVertices, indices, numOfIndices);
	}
};

class Triangle : public Primitive
{
public:
	Triangle() : Primitive()
	{
		Vertex vertices[] =
		{
			// Position                     // Color                        // Texture Coordinates  // Normals
			glm::vec3(-0.5f, 0.5f, 0.0f),   glm::vec3(1.0f, 0.0f, 0.0f),    glm::vec2(0.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(-0.5f,-0.5f, 0.0f),   glm::vec3(0.0f, 1.0f, 0.0f),    glm::vec2(0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f, -0.5f, 0.0f),   glm::vec3(0.0f, 0.0f, 1.0f),    glm::vec2(1.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f,  0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 0.0f),    glm::vec2(1.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f)
		};

		unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0,1,2
		};

		unsigned numOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, numOfVertices, indices, numOfIndices);
	}
};