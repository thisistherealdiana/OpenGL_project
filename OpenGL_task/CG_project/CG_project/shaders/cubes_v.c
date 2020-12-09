#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coord;
//layout (location = 3) in vec3 tangens;
//layout (location = 4) in vec3 bitangens;

out V_out {
    vec3 frag_pos;
    vec2 tex_coords;
    vec3 normal;
    mat3 tbn_mat;
} out_parameters;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    out_parameters.frag_pos = vec3(model * vec4(position, 1.0));   
    out_parameters.tex_coords = tex_coord;
    
    mat3 normal_matrix = transpose(inverse(mat3(model)));
    out_parameters.normal = normalize(normal_matrix * normal);

    gl_Position = projection * view * model * vec4(position, 1.0);
} 
