#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coord;
layout (location = 3) in vec3 tangens;

out V_out {
    vec3 frag_pos;
    vec2 tex_coords;
    vec3 normal;
    mat3 tbn_mat;
    vec4 position_in_s;
    mat3 inverse_tbn;
}out_parameters;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 shadowmat;

void main(){
    out_parameters.frag_pos = vec3(model * vec4(position, 1.0));   
    out_parameters.tex_coords = tex_coord;
    
    mat3 normal_matrix = transpose(inverse(mat3(model)));
    vec3 n = normalize(normal_matrix * normal);
    vec3 t = normalize(normal_matrix * tangens);
    vec3 b = normalize(cross(n, t));
    out_parameters.tbn_mat  = mat3(t, b, n);
    out_parameters.inverse_tbn = transpose(out_parameters.tbn_mat);

    out_parameters.position_in_s = shadowmat * vec4(out_parameters.frag_pos, 1.0);

    out_parameters.normal = normal;
    gl_Position = projection * view * model * vec4(position, 1.0);
} 
