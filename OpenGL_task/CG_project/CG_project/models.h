#ifndef MODEL_H
#define MODEL_H


float vertices_for_cubemirror[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

float cube_ver[] = {
            // back face
            -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, // bottom-left
             1.0f,  1.0f, -1.0f,   1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,   1.0f, 0.0f, // bottom-right         
             1.0f,  1.0f, -1.0f,   1.0f, 1.0f, // top-right
            -1.0f, -1.0f, -1.0f,   0.0f, 0.0f, // bottom-left
            -1.0f,  1.0f, -1.0f,   0.0f, 1.0f, // top-left
            // front face
            -1.0f, -1.0f,  1.0f,   0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,   1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f,   1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,   1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,   0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,   0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f,  0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f,  0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, // top-right
            // right face
             1.0f,  1.0f,  1.0f,   1.0f, 0.0f, // top-left
             1.0f, -1.0f, -1.0f,   0.0f, 1.0f, // bottom-right
             1.0f,  1.0f, -1.0f,   1.0f, 1.0f, // top-right         
             1.0f, -1.0f, -1.0f,   0.0f, 1.0f, // bottom-right
             1.0f,  1.0f,  1.0f,   1.0f, 0.0f, // top-left
             1.0f, -1.0f,  1.0f,   0.0f, 0.0f, // bottom-left     
            // bottom face
            -1.0f, -1.0f, -1.0f,   0.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,   1.0f, 1.0f, // top-left
             1.0f, -1.0f,  1.0f,   1.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,   1.0f, 0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,   0.0f, 0.0f, // bottom-right
            -1.0f, -1.0f, -1.0f,   0.0f, 1.0f, // top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, // top-left
             1.0f,  1.0f , 1.0f,   1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,   1.0f, 1.0f, // top-right     
             1.0f,  1.0f,  1.0f,   1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,   0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f, 0.0f  // bottom-left        
};


#endif
