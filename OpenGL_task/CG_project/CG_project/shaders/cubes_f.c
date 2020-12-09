#version 330 core

out vec4 color;

in V_out {
    vec3 frag_pos;
    vec2 tex_coords;
    vec3 normal;
    mat3 tbn_mat;
}input_parameter;
struct Light{
    vec3 light_pos;
    vec3 view_pos;
};
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normalMap;
    float shin_par;
};
uniform Material material;
uniform Light for_light;

void main(){
    //vec3 normal = texture(material.normalMap, fs_in.TexCoords).rgb;
    //normal = normalize(normal * 2.0f - 1.0f);

    vec3 normal = input_parameter.normal;

    vec3 diff_color = texture(material.diffuse, input_parameter.tex_coords).rgb;
    vec3 ambient = 0.33f * diff_color;


    vec3 light_dir = normalize(for_light.light_pos - input_parameter.frag_pos);
    float diff = max(dot(normal, light_dir), 0.0f);
    vec3 diffuse = diff * diff_color;

    vec3 view_dir = normalize(for_light.view_pos - input_parameter.frag_pos);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec1 = pow(max(dot(view_dir, reflect_dir), 0.00000001f), material.shin_par);
    vec3 specular =  texture(material.specular, input_parameter.tex_coords).rgb * spec1;

    float distance = length(for_light.light_pos - input_parameter.frag_pos);
    float dist_parameter = 1.0f / (1.00000001f + 0.0400001f * distance + 0.01000001f * distance * distance);

    vec3 result_color = (ambient + diffuse + specular) * dist_parameter;
    color = vec4(result_color, 1.0f);
}


