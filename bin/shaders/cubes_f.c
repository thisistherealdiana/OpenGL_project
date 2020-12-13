#version 330 core

out vec4 color;

in V_out {
    vec3 frag_pos;
    vec2 tex_coords;
    vec3 normal;
    mat3 tbn_mat;
    vec4 position_in_s;
    mat3 inverse_tbn;
}input_parameter;

struct Light{
    vec3 light_pos;
    vec3 view_pos;
    bool tr_eff;
    bool paralax;
};
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normalm;
    float shin_par;
    sampler2D shadow;
    sampler2D height_map;
};
uniform Material material;
uniform Light for_light;



vec2 my_parallax_mapping(vec2 input_tex_coords, vec3 my_view_dir, int N, int D, float height_pow){
    float layer_depth = 1.0f / N;
    float curr_depth = 0.0f;
    vec2 vec_shift = (my_view_dir.xy ) * height_pow; 
    vec2 delta = vec_shift / N;
    vec2  curr_tex_coords  = input_tex_coords;
    float curr_depth_value = 1.0f - texture(material.height_map, curr_tex_coords).r;  
    while(curr_depth < curr_depth_value){
        curr_tex_coords -= delta;
        curr_depth_value = 1.0f - texture(material.height_map, curr_tex_coords).r;  
        curr_depth += layer_depth;  
    }
    curr_tex_coords += delta;
    curr_depth -= layer_depth;  
    layer_depth *= 0.5f;
    delta *= 0.5f;
    for(int i = D; i > 0; i--){
        curr_depth_value = 1.0f - texture(material.height_map, curr_tex_coords).r;  
        layer_depth *= 0.5f;
        delta *= 0.5f;
        if(curr_depth_value > curr_depth){
            curr_tex_coords -= delta;
            curr_depth += layer_depth;
        }else{
            curr_tex_coords += delta;
            curr_depth -= layer_depth;
        }
    }
    return curr_tex_coords; 
}



float calcsh(vec3 normal, vec3 light_dir){
    vec3 pvec = input_parameter.position_in_s.xyz / input_parameter.position_in_s.w;
    pvec = pvec * 0.5 + 0.5;
    if(pvec.z > 1.0){
        return 0.0f;
    }
    float realdepth = pvec.z;
    float shadow = 0.0f;
    float shift = max(0.05f * (1.0f - abs(dot(normal, light_dir))), 0.006f);
    vec2 texel_size = 1.0 / textureSize(material.shadow, 0);
    for(int x = -1; x <= 1; x++){
        for(int y = -1; y <= 1; y++){
            float tmp = texture(material.shadow, pvec.xy + vec2(x, y) * texel_size).r;
            if(realdepth - shift > tmp){
                shadow += 1.0;
            }//////////////
        }////////////////////
    }///////////////////////
    shadow /= 9.0;
    return shadow;
}


void main(){

    vec2 new_textures_coords;
    if(for_light.paralax){
        vec3 dir_TBN = normalize(input_parameter.inverse_tbn * normalize(for_light.view_pos - input_parameter.frag_pos));
        new_textures_coords = my_parallax_mapping(input_parameter.tex_coords, dir_TBN, 10, 5, 0.010f);
    }else{
        new_textures_coords = input_parameter.tex_coords;
    }

    //vec3 normal = texture(material.normalMap, fs_in.TexCoords).rgb;
    //normal = normalize(normal * 2.0f - 1.0f);
    //vec3 normal = input_parameter.normal;
    vec3 normal = texture(material.normalm, new_textures_coords).rgb;
    normal = normalize(normal * 2.0 - 1.0);   
    normal = normalize(input_parameter.tbn_mat * normal);  

    vec3 diff_color = texture(material.diffuse, new_textures_coords).rgb;
    vec3 ambient = 0.33f * diff_color;


    vec3 light_dir = normalize(for_light.light_pos - input_parameter.frag_pos);
    float diff = max(dot(normal, light_dir), 0.0f);
    vec3 diffuse = diff * diff_color;

    vec3 view_dir = normalize(for_light.view_pos - input_parameter.frag_pos);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec1 = pow(max(dot(view_dir, reflect_dir), 0.00000001f), material.shin_par);
    vec3 specular =  texture(material.specular, new_textures_coords).rgb * spec1;

    float distance = length(for_light.light_pos - input_parameter.frag_pos);
    float dist_parameter = 1.0f / (1.0000f + 0.0400f * distance + 0.0100f * distance * distance);
    float shadow = calcsh(input_parameter.normal, light_dir);
    shadow = 1.0f - shadow;
    vec3 result_color = (ambient + (diffuse + specular)*shadow) * dist_parameter;

    if(for_light.tr_eff)
        color = vec4(result_color.r, 1.0f, result_color.b, 1.0f);
    else
        color = vec4(result_color, 1.0f);
}

/*
vec2 my_parallax_mapping(vec2 input_tex_coords, vec3 my_view_dir, int N, int D, float height_pow){
    float layer_depth = 1.0f / N;
    float curr_depth = 0.0f;
    vec2 vec_shift = (my_view_dir.xy ) * height_pow; 
    vec2 delta = vec_shift / N;
    vec2  curr_tex_coords  = input_tex_coords;
    float curr_depth_value = 1.0f - texture(material.height_map, curr_tex_coords).r;  
    while(curr_depth < curr_depth_value){
        curr_tex_coords -= delta;
        curr_depth_value = 1.0f - texture(material.height_map, curr_tex_coords).r;  
        curr_depth += layer_depth;  
    }
    curr_tex_coords += delta;
    curr_depth -= layer_depth;  
    layer_depth *= 0.5f;
    delta *= 0.5f;
    for(int i = D; i > 0; i--){
        curr_depth_value = 1.0f - texture(material.height_map, curr_tex_coords).r;  
        layer_depth *= 0.5f;
        delta *= 0.5f;
        if(curr_depth_value > curr_depth){
            curr_tex_coords -= delta;
            curr_depth += layer_depth;
        }else{
            curr_tex_coords += delta;
            curr_depth -= layer_depth;
        }
    }
    return curr_tex_coords; 
}

*/
