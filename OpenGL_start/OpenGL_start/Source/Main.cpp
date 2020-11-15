#include "libs.h"

struct Vertex
{
    float x, y, z;
    float r, g, b;
    float t_x, t_y;
};

Vertex vertices[] =
{
    // Position                 // Color                 // Texture Coordinates
    -0.5f,  0.5f, 0.0f,         1.0f, 0.0f, 0.0f,        0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f,         0.0f, 1.0f, 0.0f,        0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,          0.0f, 0.0f, 1.0f,        1.0f, 0.0f,
    0.5f,  0.5f, 0.0f,         1.0f, 1.0f, 0.0f,         1.0f, 1.0f
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

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
    glViewport(0, 0, fbW, fbH); // how much of the window we want to use (from 0,0 to width,height) canvas size
}

bool loadShaders(GLuint& program)
{
    bool loadSuccess = true;
    char infolog[512]; // for error messages
    GLint success;

    std::string temp = "";
    std::string source = "";

    std::fstream in_file;

    //Vertex 
    in_file.open("./Source/vertex_core.txt");

    if (in_file.is_open())
    {
        while (std::getline(in_file, temp))
        {
            source = source + temp + "\n";
        }
    }
    else
    {
        std::cout << "Can't Open Vertex File" << std::endl;
        loadSuccess = false;
    }

    in_file.close();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // to create Vertex Shader ID
    const GLchar* vertexSource = source.c_str();
    glShaderSource(vertexShader, 1, &vertexSource, NULL); // to set the source to the just created shader
    glCompileShader(vertexShader); // to compile our shader 

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "Can't Compile Vertex Shader" << std::endl << infolog << std::endl;
        loadSuccess = false;
    }

    temp = "";
    source = "";

    //Fragment
    //in_file.open("C:/Users/Lenovo/Desktop/OpenGL/OpenGL_start/OpenGL_start/Source/fragment_core.txt");
    in_file.open("./Source/fragment_core.txt");

    if (in_file.is_open())
    {
        while (std::getline(in_file, temp))
        {
            source = source + temp + "\n";
        }
    }
    else
    {
        std::cout << "Can't Open Fragment File" << std::endl;
        loadSuccess = false;
    }

    in_file.close();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // to create Fragment Shader ID
    const GLchar* fragmentSource = source.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // to set the source to the just created shader
    glCompileShader(fragmentShader); // to compile our shader 

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "Can't Compile Fragment Shader" << std::endl << infolog << std::endl;
        loadSuccess = false;
    }

    temp = "";
    source = "";

    //Program
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infolog);
        std::cout << "Can't Link the Program" << std::endl << infolog << std::endl;
        loadSuccess = false;
    }

    //End
    glUseProgram(0); // to reset the program we are currently using
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return loadSuccess;
}

int main()
{
    // Initialize the GLFW library 
    if (!glfwInit())
    {
        std::cout << "Can't Initialize the GLFW library" << std::endl;
        return -1;
    }

    // Create the window
    const int WINDOW_WIDTH = 640;       //frame
    const int WINDOW_HEIGHT = 480;
    int framebufferWidth = 0;           //canvas
    int framebufferHeight = 0;

    //Set Window Options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL version we want to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // use the core-profile
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // not able to resize the window

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); на маке

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MY PROGRAM", NULL, NULL);
    if (window == NULL) 
    {
        std::cout << "Can't Create the Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // set the context to the window
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    
    // Initialize the GLAD library
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Can't Initialize the GLAD library" << std::endl;
        glfwTerminate();
        return -1;
    }

    //OpenGL options
    
    //glEnable(GL_DEPTH_TEST);    // how far away the fragment is
    glEnable(GL_CULL_FACE); // to not show the back of the triangle
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // Initialize the shader
    GLuint core_program;
    
    if (!loadShaders(core_program))
    {
        glfwTerminate();
        return -1;
    }
    
    //VAO, VBO, EBO
    GLuint VAO, VBO, EBO;

    // Generate VAO and Bind
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate VBO and Bind and send Vertex Data to the GPU
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // to draw and not to change values often

    // Generate EBO and Bind and send Indice Data to the GPU
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // to draw and not to change values often

    // Set VertexAttributePoinnters an enable - to tell GPU where the color position and tex coordinates are
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Texture Unit

    GLuint texture0;
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// s and t = x and y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    int image_width = 0;
    int image_height = 0;
    int numOfChannels;
    unsigned char* image = stbi_load("./Source/Images/spongebob.png",&image_width, &image_height, &numOfChannels, 0);

    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Can't Load Image" << std::endl;
    }
    
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);

    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// s and t = x and y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    int image_width1 = 0;
    int image_height1 = 0;
    int numOfChannels1;
    unsigned char* image1 = stbi_load("./Source/Images/seaworld.png", &image_width1, &image_height1, &numOfChannels1, 0);

    if (image1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width1, image_height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Can't Load Image" << std::endl;
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image1);


    // Main Loop - to keep drawing until we tell GLFW to stop
    while (!glfwWindowShouldClose(window)) 
    {
        // Update Input
        processInput(window);

        // Clear
        glClearColor(0.3f, 0.8f, 0.7f, 1.0f);    //to specify the color we want after we clear the buffer
        glClear(GL_COLOR_BUFFER_BIT);   //to clear the buffer: GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT

        // Use a Program
        glUseProgram(core_program);

        // Update Uniforms
        glUniform1i(glGetUniformLocation(core_program, "texture0"), 0);
        glUniform1i(glGetUniformLocation(core_program, "texture1"), 1);

        // Activate Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);

        //Bind Vertex Array Object
        glBindVertexArray(VAO);

        // Draw
        //glDrawArrays(GL_TRIANGLES, 0, numOfVertices);
        glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window); // to swap the color buffer - that contains color values for each pixel in window
        glfwPollEvents();   // to check if any keyboard input or mouse movement happened 
    
        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // End of Program
    glfwDestroyWindow(window);
    glfwTerminate();
    glDeleteProgram(core_program);
    return 0;
}