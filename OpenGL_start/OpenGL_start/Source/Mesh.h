#pragma once
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Vertex.h"
#include "Primitives.h"

class Mesh
{
private:
	unsigned numOfVertices;
	unsigned numOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 ModelMatrix;

    void initVertexArrayObject(Primitive* primitive)
    {
        // Set
        numOfVertices = primitive->getNumOfVertices();
        numOfIndices = primitive->getNumOfIndices();

        // Generate VAO
        glGenVertexArrays(1, &VAO); //glCreateVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Generate VBO and Bind and send Vertex Data to the GPU
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, numOfVertices * sizeof(Vertex), primitive->getVertices(), GL_STATIC_DRAW); // to draw and not to change values often

        // Generate EBO and Bind and send Indice Data to the GPU
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfIndices * sizeof(GLuint), primitive->getIndices(), GL_STATIC_DRAW); // to draw and not to change values often

        // Set VertexAttributePoinnters an enable - to tell GPU where the color position and tex coordinates are
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(float)));
        glEnableVertexAttribArray(3);

        glBindVertexArray(0);
    }


    // VAO
    void initVertexArrayObject(Vertex* vertexArray, const unsigned& numOfVertices, GLuint* indexArray, const unsigned& numOfIndices)
    {
        // Set
        this->numOfVertices = numOfVertices;
        this->numOfIndices = numOfIndices;

        // Generate VAO
        glGenVertexArrays(1, &VAO); //glCreateVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Generate VBO and Bind and send Vertex Data to the GPU
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, this->numOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW); // to draw and not to change values often

        // Generate EBO and Bind and send Indice Data to the GPU
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numOfIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW); // to draw and not to change values often

        // Set VertexAttributePoinnters an enable - to tell GPU where the color position and tex coordinates are
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(float)));
        glEnableVertexAttribArray(3);

        glBindVertexArray(0);
    }

    void updateUniforms(Shader* shader)
    {
        shader->setMat4fv(ModelMatrix, "ModelMatrix");
    }

    void updateModelMatrix()
    {
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, position);
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::scale(ModelMatrix, scale);
    }


public:
    Mesh(Primitive* primitive, glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f))
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
        this->initVertexArrayObject(primitive);
        this->updateModelMatrix();
    }

	Mesh(Vertex* vertexArray, const unsigned& numOfVertices, GLuint* indexArray, const unsigned& numOfIndices,
        glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f))
	{
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
        this->initVertexArrayObject(vertexArray, numOfVertices, indexArray, numOfIndices);
        this->updateModelMatrix();
	}

	~Mesh()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    // Accessors

    // Modifiers
    void setPosition(const glm::vec3 position)
    {
        this->position = position;
    }

    void setRotation(const glm::vec3 rotation)
    {
        this->rotation = rotation;
    }

    void setScale(const glm::vec3 scale)
    {
        this->scale = scale;
    }

    // Functions
    void move(const glm::vec3 position)
    {
        this->position += position;
    }

    void rotate(const glm::vec3 rotation)
    {
        this->rotation += rotation;
    }

    void scaleUp(const glm::vec3 scale)
    {
        this->scale += scale;
    }

    void update()
    {

    }

    void render(Shader* shader)
    {
        // Update Uniforms
        this->updateModelMatrix();
        this->updateUniforms(shader);

        shader->use();

        // Bind Vertex Array Object
        glBindVertexArray(VAO);

        // Draw - Render
        /*
        if (indices.empty())
            glDrawArrays(GL_TRIANGLES, 0, numOfVertices);
        else*/
            glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0);
    }
};