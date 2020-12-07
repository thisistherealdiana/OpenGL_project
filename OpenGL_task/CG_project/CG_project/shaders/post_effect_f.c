#version 330 core

in vec2 tex_coord;

out vec4 color;

uniform sampler2D screen_texture;

void main(){   
    vec4 tmp_color =  texture(screen_texture, tex_coord);
    float gr = 0.21 * tmp_color.r + 0.72 * tmp_color.g + 0.07 * tmp_color.b;
    color = vec4(0.0, gr,  0.0, 1.0);
}

