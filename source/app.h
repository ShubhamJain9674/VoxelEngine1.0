#pragma once


#include "utility.h"

#include <GLM/glm.hpp>

// testing
#include "block.h"
#include "memory.h"
#include "camera.h"

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

    float GetAspectRatio();

private:

	GLFWwindow* _window{ nullptr };
    
    // deltatime management.
    double _deltaTime{ 0.0 };
    double _lastTime{ 0.0 };
    double _timeElapsed{ 0.0 };

    // view 
  
    // In degree
    float _fov{ 45.0f };
    float _nearClip{ 1.0f };
    float _farClip{ 100.0f };


    // testing
    std::unique_ptr<Voxel> t_voxel{nullptr};
    std::unique_ptr<Shader> t_shader{ nullptr };

    RenderData _renderData;

    std::unique_ptr<Camera> _camera{nullptr};


    float angle = 0.0f;
};
