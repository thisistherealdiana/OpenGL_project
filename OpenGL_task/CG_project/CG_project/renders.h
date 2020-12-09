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
        "./textures/sky_box/posx.jpg",        "./textures/sky_box/negx.jpg",        "./textures/sky_box/posy.jpg",     
        "./textures/sky_box/negy.jpg",        "./textures/sky_box/posz.jpg",        "./textures/sky_box/negz.jpg"     
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

GLuint bilboard_setVAO(){
    GLuint VAO, VBO;
    float bvertices[] = {
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,    
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,        1.0f,  0.5f,  0.0f,  1.0f,  0.0f    };
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bvertices), bvertices, GL_STATIC_DRAW); 
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    return VAO;
}



GLuint bilboard_texture(const char * path){
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    int  tex_width, tex_height, npix;
    unsigned char * image = stbi_load(path, &tex_width, &tex_height, &npix, 0);
    if(image == NULL){
        std::cout << "ERROR texture open" << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}


int funccmp( const void * val1, const void * val2 );
glm::vec3 local_camera_pos;
int drow_bilbords( GLuint sh , GLuint vao, GLuint btexture, glm::mat4 view, glm::mat4 projection, glm::vec3 camera_pos ){
     glm::vec3 bilboard_position[] = {
  glm::vec3(3.2f,  0.5f,  2.0f),   glm::vec3(3.9f,  0.5f,  3.0f),     glm::vec3(3.2f,  0.5f,  4.0f),    glm::vec3(3.9f,  0.5f,  5.0f),
  glm::vec3(3.2f,  0.5f,  6.0f), glm::vec3(3.9f,  0.5f,  7.0f) };
    local_camera_pos = camera_pos;
    qsort(&bilboard_position, 6, sizeof(glm::vec3), funccmp);
    glUseProgram(sh);  
    for(int i = 0; i < 6; i++){
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, bilboard_position[i]);
        glUniformMatrix4fv(glGetUniformLocation(sh, "model"), 1, GL_FALSE, glm::value_ptr(model));      
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, btexture);
        glUniformMatrix4fv(glGetUniformLocation(sh, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(sh, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1i(glGetUniformLocation(sh, "my_texture"), 0);
        glBindVertexArray(vao); 
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0); 
    }
    return 0;
}
int funccmp( const void * val1, const void * val2 ){
    glm::vec3 d1 = *(glm::vec3 *)(val1);
    glm::vec3 d2 = *(glm::vec3 *)(val2);
    float dist1, dist2;
    dist1 = glm::length(local_camera_pos - d1); 
    dist2 = glm::length(local_camera_pos - d2);
    if(dist1 > dist2){
        return 0;
    }
    return 1;
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




int drow_p_effect(GLuint shad, GLuint texture, GLuint vao){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shad);  
    glBindVertexArray(vao);
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shad, "screen_texture"), 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);  
    glEnable(GL_DEPTH_TEST);
    return 0;
}

int set_p_buffer(GLuint &framebuffer1, GLuint &texture_color_buffer, int w, int h){
    glGenFramebuffers(1, &framebuffer1);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1);  
    glGenTextures(1, &texture_color_buffer);
    glBindTexture(GL_TEXTURE_2D, texture_color_buffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_color_buffer, 0); 
    unsigned int RBO;
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return 0;
}

float post_quad_vertices[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,         1.0f,  1.0f,  1.0f, 1.0f   };

GLuint set_p_vao(){
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(post_quad_vertices), post_quad_vertices, GL_STATIC_DRAW); 
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    return VAO;
}



GLfloat plane_vertices_main[] = {
///////////////////////////////////////
         10.0f, -0.0f,  10.0f, 0.0f, 0.1f, 0.0f,  5.0f, 0.0f,
        -10.0f, -0.0f,  10.0f, 0.0f, 0.1f, 0.0f,  0.0f, 0.0f,//
        -10.0f, -0.0f, -10.0f, 0.0f, 0.1f, 0.0f,  0.0f, 5.0f,
         10.0f, -0.0f,  10.0f, 0.0f, 0.1f, 0.0f,  5.0f, 0.0f,//
        -10.0f, -0.0f, -10.0f, 0.0f, 0.1f, 0.0f,  0.0f, 5.0f,
         10.0f, -0.0f, -10.0f, 0.0f, 0.1f, 0.0f,  5.0f, 5.0f//
        //         10.0f, -0.0f, -10.0f, 0.0f, 0.1f, 0.0f,  5.0f, 5.0f         10.0f, -0.0f, -10.0f, 0.0f, 0.1f, 0.0f,  5.0f, 5.0f
    };
GLuint set_plane_vao1(){
    GLuint vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertices_main), plane_vertices_main, GL_STATIC_DRAW); 
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(2); 
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return vao;
}

class Material{
public:
    GLuint diffuse;
    GLuint specular;
    float shin;
};


int load_textures(Material &material){
    int  tex_width, tex_height, n;
    unsigned char * image;
    GLuint new_texture;
    glGenTextures(1, &new_texture);
    glBindTexture(GL_TEXTURE_2D, new_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    image = stbi_load("./textures/Tiles_05local/Tiles_05_basecolor.jpg", &tex_width, &tex_height, &n, 0);
    if(image == NULL)
    {
        std::cout << "error open diffuse texture" << std::endl;
        return 1;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);
material.diffuse = new_texture;


    glGenTextures(1, &new_texture);
    glBindTexture(GL_TEXTURE_2D, new_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    image = stbi_load("./textures/Tiles_05local/Tiles_05_glossiness.jpg", &tex_width, &tex_height, &n, 0);
    if(image == NULL)
    {
        std::cout << "error open specular texture " << std::endl;
        return  1;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0,  GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);
material.specular = new_texture;

    return 0;
}

int drow_plane1(GLuint shad, GLuint vao, Material material_l, glm::vec3 camera_pos, glm::vec3 light_pos,  glm::mat4 model,  glm::mat4 view, glm::mat4 projection){
        glUseProgram(shad);
        glUniformMatrix4fv(glGetUniformLocation(shad, "model"), 1, GL_FALSE, glm::value_ptr(model));     
        glUniformMatrix4fv(glGetUniformLocation(shad, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shad, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3fv(glGetUniformLocation(shad, "for_light.view_pos"), 1, glm::value_ptr(camera_pos));        
        glUniform3fv(glGetUniformLocation(shad, "for_light.light_pos"), 1, glm::value_ptr(light_pos));   
        glUniform1f(glGetUniformLocation(shad,"material.shin_par"), material_l.shin);//0.65f * 128.0f
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material_l.diffuse);
        glUniform1i(glGetUniformLocation(shad, "material.diffuse"), 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, material_l.specular);
        glUniform1i(glGetUniformLocation(shad, "material.specular"), 1);

        glBindVertexArray(vao); 
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0); 
        return 0;
}


#endif
