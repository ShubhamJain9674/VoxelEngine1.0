#pragma once


#include "utility.h"

// testing
#include "block.h"
#include "memory.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define APP_NAME "Voxel Engine v-1.0"

#define FRAME_RATE 60.0
#define FRAME_DELTA (1 / FRAME_RATE)



class App
{

public:
    App();
    ~App();
    
    bool  Init();
    void Run();
    void Cleanup();

private:

    void Update(double DeltaTime);
    void Render();

private:

	GLFWwindow* _window{ nullptr };
    
    // deltatime management.
    double _deltaTime{ 0.0 };
    double _lastTime{ 0.0 };
    double _timeElapsed{ 0.0 };

    // testing
    std::unique_ptr<Voxel> t_voxel{nullptr};

};
