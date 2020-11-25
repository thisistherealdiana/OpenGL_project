#pragma once
#include <glad/glad.h> 
#include <gl/GL.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include "stb_image.h"

class Texture
{
private:
	GLuint id;
	int height;
	int width;
    unsigned int type;

public:
	Texture(const char* fileName, GLenum type)
	{
        this->type = type;

        glGenTextures(1, &id);
        glBindTexture(type, id);

        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);	// (s and t) = (x and y)
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        int numOfChannels;
        unsigned char* image = stbi_load(fileName, &width, &height, &numOfChannels, 0);

        if (image)
        {
            glTexImage2D(type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(type);
        }
        else
        {
            std::cout << "TEXTURE: Can't Load Image: " << fileName << std::endl;
        }

        glActiveTexture(0);
        glBindTexture(type, 0);
        stbi_image_free(image);
	}

	~Texture()
	{
		glDeleteTextures(1, &id);
	}

    GLuint getID() const
    {
        return id;
    }

    void bind(const GLint texture_unit)
    {
        glActiveTexture(GL_TEXTURE0 + texture_unit);
        glBindTexture(type, id);
    }

    void unbind()
    {
        glActiveTexture(0);
        glBindTexture(type, 0);
    }
};