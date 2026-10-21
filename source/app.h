#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "utility.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define APP_NAME "Voxel Engine v-1.0"





class App
{

public:
    App();
    ~App();
    
    bool  Init();
    void Run();
    void Cleanup();

private:

    void HandleEvents();

private:

	GLFWwindow* _window{ nullptr };
    

};
