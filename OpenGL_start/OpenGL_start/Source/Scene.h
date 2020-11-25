#pragma once
#include "libs.h"

enum shader_enum { SHADER_CORE_PROGRAM = 0 };
enum texture_enum { TEX_SPONGEBOB = 0, TEX_SEAWORLD = 1 };
enum material_enum { MAT_1 = 0 };
enum mesh_enum { MESH_QUAD = 0 };

class Scene
{
private:
// Variables
	// Window
	GLFWwindow* window;
	const int WINDOW_WIDTH;       //frame
	const int WINDOW_HEIGHT;
	int framebufferWidth;           //canvas
	int framebufferHeight;

	//Matrices
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;      // behind the camera, not right in the camera
	float farPlane;       // distance

	// Shaders
	std::vector<Shader*> shaders;

	// Textures
	std::vector<Texture*> textures;

	//Materials
	std::vector<Material*> materials;

	// Meshes
	std::vector<Mesh*> meshes;

	// Lights
	std::vector<glm::vec3*> lights;


// Static variables

// Private functions
	void initGLFW()
	{
		// Initialize the GLFW library 
		if (!glfwInit())
		{
			std::cout << "SCENE: Can't Initialize the GLFW library" << std::endl;
		}
	}
	
	void initWindow(const char * title, bool resizable)
	{
		//Set Window Options
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL version we want to use
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // use the core-profile
		glfwWindowHint(GLFW_RESIZABLE, resizable); // (not) able to resize the window

		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); на маке

		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "SCENE: Can't Create the Window" << std::endl;
			glfwTerminate();
		}

		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

		glfwMakeContextCurrent(window); // set the context to the window
		glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

		glfwMakeContextCurrent(window);
	}
	
	void initGLAD()
	{
		// Initialize the GLAD library
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "SCENE: Can't Initialize the GLAD library" << std::endl;
			glfwTerminate();		
		}
	}
	
	void initOpenGLOptions()
	{
		//OpenGL options
		//glEnable(GL_DEPTH_TEST);    // how far away the fragment is
		glEnable(GL_CULL_FACE); // to not show the back of the triangle
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void initMatrices()
	{
		ViewMatrix = glm::mat4(1.0f);
		ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp); // moving the front vector if position has been changed

		ProjectionMatrix = glm::mat4(1.0f);
		ProjectionMatrix = glm::perspective(glm::radians(fov), (float)(framebufferWidth) / (float)framebufferHeight, nearPlane, farPlane);
	}

	void initShaders()
	{
		shaders.push_back(new Shader("./Source/vertex_core.txt", "./Source/fragment_core.txt"));
	}

	void initTextures()
	{
		textures.push_back(new Texture("./Source/Images/spongebob.png", GL_TEXTURE_2D));
		textures.push_back(new Texture("./Source/Images/seaworld.png", GL_TEXTURE_2D));
	}

	void initMaterials()
	{
		materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 0, 1));
	}

	void initMeshes()
	{
		meshes.push_back(new Mesh(&Quad()));
		meshes.push_back(new Mesh(&Quad()));
	}

	void initLights()
	{
		lights.push_back( new glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void initUniforms()
	{
		// Matrices
		shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");
		shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");

		// Lights
		shaders[SHADER_CORE_PROGRAM]->setVec3f(*lights[0], "lightPos0");
		shaders[SHADER_CORE_PROGRAM]->setVec3f(camPosition, "camPosition");
	}

	void updateUniforms()
	{
		// if we reframe the window we need to update info in ProjectionMatrix
		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

		glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(fov), float(framebufferWidth) / framebufferHeight, nearPlane, farPlane);
		shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");
	}

public:
// Constructors
	Scene(const char* title, const int width, const int height, bool resizable) : WINDOW_WIDTH(width), WINDOW_HEIGHT(height)
	{
		window = NULL;
		framebufferHeight = WINDOW_HEIGHT;
		framebufferWidth = WINDOW_WIDTH;

		camPosition = glm::vec3(0.0f, 0.0f, 1.0f);
		worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		camFront = glm::vec3(0.0f, 0.0f, -1.0f);
		fov = 90.0f;
		nearPlane = 0.1f;       
		farPlane = 1000.0f;     

		this->initGLFW();
		this->initWindow(title, resizable);
		this->initGLAD();
		this->initOpenGLOptions();
		this->initMatrices();
		this->initShaders();
		this->initTextures();
		this->initMaterials();
		this->initMeshes();
		this->initLights();
		this->initUniforms();
	}

// Destructor
	virtual ~Scene()
	{
		glfwDestroyWindow(window);
		glfwTerminate();

		for (size_t i = 0; i < shaders.size(); i++)
		{
			delete shaders[i];
		}
		for (size_t i = 0; i < textures.size(); i++)
		{
			delete textures[i];
		}
		for (size_t i = 0; i < materials.size(); i++)
		{
			delete materials[i];
		}
		for (size_t i = 0; i < meshes.size(); i++)
		{
			delete meshes[i];
		}
		for (size_t i = 0; i < lights.size(); i++)
		{
			delete lights[i];
		}
	}

// Accessors
	int getWindowShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

// Modifiers
	void setWindowShouldClose()
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

// Functions
	void update()
	{
		// Update Input
		glfwPollEvents();	// to check if any keyboard input or mouse movement happened 
		this->processInput(window);
		this->processInput(window, *meshes[MESH_QUAD]);
	}

	void render()
	{
		// Update
		//updateInput(window);

		// Clear
		glClearColor(0.3f, 0.8f, 0.7f, 1.0f);    //to specify the color we want after we clear the buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);   //to clear the buffer: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT

		// Update Uniforms
		updateUniforms();
		materials[MAT_1]->sendToShader(*shaders[SHADER_CORE_PROGRAM]);

		// Use a Program
		shaders[SHADER_CORE_PROGRAM]->use();

		// Activate Texture
		textures[TEX_SPONGEBOB]->bind(0);
		textures[TEX_SEAWORLD]->bind(1);

		// Draw
		meshes[MESH_QUAD]->render(shaders[SHADER_CORE_PROGRAM]);

		/*
		textures[TEX_SPONGEBOB]->bind(1);
		textures[TEX_SEAWORLD]->bind(0);
		meshes[1]->render(shaders[SHADER_CORE_PROGRAM]);
		*/

		// End Draw
		glfwSwapBuffers(window); // to swap the color buffer - that contains color values for each pixel in window
		glFlush();

		// Reset
		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

// Static functions
	static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
	{
		glViewport(0, 0, fbW, fbH); // how much of the window we want to use (from 0,0 to width,height) canvas size
	}

	static void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	static void processInput(GLFWwindow* window, Mesh& mesh)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			mesh.move(glm::vec3(0.0f, 0.0f, -0.01f));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			mesh.move(glm::vec3(0.0f, 0.0f, 0.01f));
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			mesh.move(glm::vec3(-0.01f, 0.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			mesh.move(glm::vec3(0.01f, 0.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			mesh.rotate(glm::vec3(0.0f, -1.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			mesh.rotate(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			mesh.scaleUp(glm::vec3(0.01f));
		}
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			mesh.scaleUp(glm::vec3(-0.01f));
		}
	}
};
