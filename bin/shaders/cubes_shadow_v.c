#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coord;
layout (location = 3) in vec3 tangens;

uniform mat4 model;
uniform mat4 shadowmat;

void main(){
    gl_Position = shadowmat * model * vec4(position, 1.0);
} 


