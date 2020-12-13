#ifndef GLFWWIN_H
#define GLFWWIN_H

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
int my_camera_step();



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);
    if(key == GLFW_KEY_W){
        if(action == GLFW_PRESS){
            camera.keystate[1] = true;
        }else if(action == GLFW_RELEASE){
            camera.keystate[1] = false;
        }
    }
    if(key == GLFW_KEY_S){
        if(action == GLFW_PRESS){
            camera.keystate[3] = true;
        }else if(action == GLFW_RELEASE){
            camera.keystate[3] = false;
        }
    }
    if(key == GLFW_KEY_A){
        if(action == GLFW_PRESS){
            camera.keystate[0] = true;
        }else if(action == GLFW_RELEASE){
            camera.keystate[0] = false;
        }
    }
    if(key == GLFW_KEY_D){
        if(action == GLFW_PRESS){
            camera.keystate[2] = true;
        }else if(action == GLFW_RELEASE){
            camera.keystate[2] = false;
        }
    }
    if(key == GLFW_KEY_G){
        if(action == GLFW_PRESS){
            if(post_effect){
                post_effect = false;
            }else{
                post_effect = true;
            }
        }
    }
    if(key == GLFW_KEY_P){
        if(action == GLFW_PRESS){
            if(paralax){
                paralax = false;
            }else{
                paralax = true;
            }
        }
    }
}

void mouse_callback(GLFWwindow* window, double x_pos, double y_pos){
    if(camera.first_mouse){
        camera.last_x = x_pos;
        camera.last_y = y_pos;
        camera.first_mouse = false;
    }
    GLfloat x_offset = x_pos - camera.last_x;
    GLfloat y_offset = camera.last_y - y_pos; 
    camera.last_x = x_pos;
    camera.last_y = y_pos;
/*****************************************************/
    GLfloat mouse_sensitivity = 0.05;
    x_offset *= mouse_sensitivity;
    y_offset *= mouse_sensitivity;
    camera.yaw   += x_offset;
    camera.pitch += y_offset;
    if(camera.pitch > 89.0f){
        camera.pitch = 89.0f;
    }else   if(camera.pitch < -89.0f){
        camera.pitch = -89.0f;
    }
/***************************************************/
}
int my_camera_step(){
    GLfloat new_time = glfwGetTime();
    camera.delta_time = new_time - camera.last_time;
    camera.last_time = new_time;
    GLfloat speed = 1.8f * camera.delta_time;

    glm::vec3 dirfront;
    dirfront.x = cos(camera.pitch * 0.017453f) * cos(camera.yaw * 0.017453f);
    dirfront.y = sin(camera.pitch * 0.017453f);
    dirfront.z = cos(camera.pitch * 0.017453f) * sin(camera.yaw * 0.017453f);
    camera.camera_front = glm::normalize(dirfront);

    if(camera.keystate[1] == true)
        camera.camera_pos += speed * camera.camera_front;
    if(camera.keystate[3] == true)
        camera.camera_pos -= speed * camera.camera_front;
    if(camera.keystate[0] == true)
        camera.camera_pos -= glm::normalize(glm::cross(camera.camera_front, camera.camera_up)) * speed;
    if(camera.keystate[2] == true)
        camera.camera_pos += glm::normalize(glm::cross(camera.camera_front, camera.camera_up)) * speed;
    return 0;
}


#endif
