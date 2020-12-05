#ifndef RENDER_H
#define RENDER_H
#include "models.h"
#include "my_stb.h"
int my_drow_light(GLuint vao, GLuint sh, glm::mat4 model,  glm::mat4 view, glm::mat4 projection);
GLuint my_set_light_vao();


int my_drow_light(GLuint vao, GLuint sh, glm::mat4 model,  glm::mat4 view, glm::mat4 projection){
    glUseProgram(sh);
    glUniformMatrix4fv(glGetUniformLocation(sh, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(sh, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(sh, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    return 0;
}

GLuint my_set_light_vao(){
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_ver), cube_ver, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);

    return VAO;
}


GLuint set_skybox_vao(){
    float skyboxVertices[] = {
    -1.0f,  1.0f, -1.0f,    -1.0f, -1.0f, -1.0f,     1.0f, -1.0f, -1.0f,     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,    -1.0f,  1.0f, -1.0f,    -1.0f, -1.0f,  1.0f,    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,    -1.0f,  1.0f, -1.0f,    -1.0f,  1.0f,  1.0f,    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,     1.0f, -1.0f,  1.0f,     1.0f,  1.0f,  1.0f,     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,     1.0f, -1.0f, -1.0f,    -1.0f, -1.0f,  1.0f,    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,     1.0f,  1.0f,  1.0f,     1.0f, -1.0f,  1.0f,    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,     1.0f,  1.0f, -1.0f,     1.0f,  1.0f,  1.0f,     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,    -1.0f,  1.0f, -1.0f,    -1.0f, -1.0f, -1.0f,    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,     1.0f, -1.0f, -1.0f,    -1.0f, -1.0f,  1.0f,     1.0f, -1.0f,  1.0f
    };
    GLuint sky_VAO;
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &sky_VAO);
    glBindVertexArray(sky_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW); 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    return sky_VAO;
}

GLuint set_skybox_tex( ){
    GLuint sky_texture;
    const char *  textured_cube[] = {
        "../textures/sky_box/posx.jpg",        "../textures/sky_box/negx.jpg",        "../textures/sky_box/posy.jpg",     
        "../textures/sky_box/negy.jpg",        "../textures/sky_box/posz.jpg",        "../textures/sky_box/negz.jpg"     
        };
    glGenTextures(1, &sky_texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, sky_texture);
    unsigned char *data;
    int tex_width , tex_height, n; 
    for(unsigned int i = 0; i < 6; i++)
    {    
        data = stbi_load(textured_cube[i], &tex_width, &tex_height, &n, 0);
        if(data == NULL){
            std::cout << "ERROR SKYBOX texture" << std::endl;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);

    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); 
    return sky_texture;
}


int drow_skybox(GLuint sky_VAO, GLuint sh, GLuint sky_tex, glm::mat4 model, glm::mat4 view, glm::mat4 projection){
glDepthFunc(GL_LEQUAL); 
        glUseProgram(sh);  
        glBindVertexArray(sky_VAO);
        view = glm::mat4(glm::mat3(view));  
        glUniformMatrix4fv(glGetUniformLocation(sh, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(sh, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, sky_tex);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0); 
glDepthFunc(GL_LESS); 
    return 0;
}



GLuint set_mirrorcube_vao(){
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_for_cubemirror), vertices_for_cubemirror, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    return VAO;
}

int drow_mirrorcube(GLuint mirrorcube, GLuint shadr, glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 cam_pos,  GLuint sky_texture){
        glUseProgram(shadr);  
        glBindVertexArray(mirrorcube);
        glUniformMatrix4fv(glGetUniformLocation(shadr, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shadr, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shadr, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3fv(glGetUniformLocation(shadr, "camera_pos"), 1, glm::value_ptr(cam_pos));   
        glBindTexture(GL_TEXTURE_CUBE_MAP, sky_texture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0); 

    return 0;
}

#endif
