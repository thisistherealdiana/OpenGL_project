#include "libs.h"

int main()
{
    Scene scene("MY PROGRAM", 640, 480, true);

    // Main Loop - to keep drawing until we tell GLFW to stop
    while (!scene.getWindowShouldClose()) 
    {
        // Update Input
        scene.update();
        scene.render();
    }
    return 0;
}