#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "glm/vec3.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shaders.h"
#include "models.h"
#include "renders.h"

class myCamera{
public:
    GLfloat delta_time;
    GLfloat last_time;
    GLfloat yaw;
    GLfloat pitch;
    GLfloat last_x;
    GLfloat last_y;
    bool first_mouse;
    float screen_width, screen_height;
    bool keystate[4]; // for key    A W D S
    glm::vec3 camera_pos;
    glm::vec3 camera_front;
    glm::vec3 camera_up;
}camera;
bool post_effect;
#include "glfwwin.h"


int main(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    camera.screen_width = 1200;
    camera.screen_height = 800;
    GLFWwindow* window = glfwCreateWindow(camera.screen_width, camera.screen_height, "OpenGLWindow", nullptr, nullptr);
    if (window == nullptr){
	    std::cout << " Error create GLFW window " << std::endl;
	    glfwTerminate();
	    return 0;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);  
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();  //glGetError();
    if (err != GLEW_OK){
        std::cout << " Error glewInit " << glGetError() << std::endl;
        return 0;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
camera.yaw   = -90.0f;
camera.pitch = 0.0f;
camera.last_x = 400;
camera.last_y = 300;
camera.camera_pos   = glm::vec3(3.0f, 0.0f,  3.0f);
camera.camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
camera.camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);
camera.first_mouse = true;
camera.last_time = glfwGetTime();
camera.delta_time = 0;
for(int i = 0; i < 4; i++){
    camera.keystate[i] = false;
}
    int wwidth, wheight;
    glfwGetFramebufferSize(window, &wwidth, &wheight);
    glViewport(0, 0, wwidth, wheight);
/***************************************SHADERS*************************************/
    GLuint light_shad = comp_shader("./shaders/cb_light_v.c", "./shaders/cb_light_f.c");
    GLuint light_vao = my_set_light_vao();

    GLuint vao_skybox = set_skybox_vao();
    GLuint tex_skybox = set_skybox_tex();
    GLuint sh_skybox = comp_shader("./shaders/skybox_v.c", "./shaders/skybox_f.c");

    GLuint mirr_cube_shad = comp_shader("./shaders/mirror_cube_v.c", "./shaders/mirror_cube_f.c");
    GLuint mirr_cube_vao = set_mirrorcube_vao();
    
    GLuint b_texture = bilboard_texture("./textures/bilboard.png");
    GLuint b_vao =  bilboard_setVAO();
    GLuint b_sh = comp_shader("./shaders/bilboard_plane_v.c", "./shaders/bilboard_plane_f.c");

    post_effect = false;
    GLuint post_texture, post_buffer;
    set_p_buffer(post_buffer, post_texture, camera.screen_width, camera.screen_height);
    GLuint post_vao =  set_p_vao();
    GLuint post_shad = comp_shader("./shaders/post_effect_v.c", "./shaders/post_effect_f.c");


    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        my_camera_step();
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if(post_effect){
            glBindFramebuffer(GL_FRAMEBUFFER, post_buffer);
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
        }

        glm::mat4 model(1.0f);
        glm::mat4 view = glm::lookAt(camera.camera_pos, camera.camera_pos + camera.camera_front, camera.camera_up);
        glm::mat4 projection = glm::perspective(0.78539f, camera.screen_width / camera.screen_height, 0.1f, 100.0f);
        
        my_drow_light(light_vao, light_shad, model, view, projection);

        drow_mirrorcube( mirr_cube_vao, mirr_cube_shad,  glm::translate(glm::mat4(1.0f), glm::vec3(6.5f, 0.0f, 4.0f)),  view,  projection, camera.camera_pos,   tex_skybox);

        drow_skybox(vao_skybox,  sh_skybox, tex_skybox ,  model, view,  projection);
        drow_bilbords(  b_sh ,  b_vao,  b_texture,  view, projection,  camera.camera_pos );

        if(post_effect){
            drow_p_effect( post_shad,  post_texture,  post_vao);
        }
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}



