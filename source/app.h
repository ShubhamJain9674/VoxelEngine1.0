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

    static float GetMouseXDelta();
    static float GetMouseYDelta();

private:

    void Update(double DeltaTime);
    
    // Input handling.
    static void HandleKeys(GLFWwindow* window,int key,
                           int code,int action,
                           int mode);

    static void HandleMouse(GLFWwindow* window, double xPos, double yPos);


    // Render
    void Render();
    void WireFrameRenderHandler();


    
    float GetAspectRatio();



private:

	GLFWwindow* _window{ nullptr };
    
    // deltatime management.
    double _deltaTime{ 0.0 };
    double _lastTime{ 0.0 };
    double _timeElapsed{ 0.0 };

    // rendering : view 
  
    // In degree
    float _fov{ 45.0f };
    float _nearClip{ 1.0f };
    float _farClip{ 100.0f };

    // rendering : debug
    bool _wireframe_render{ false };
    bool _wireframe_trigger_press{ true };


    // testing
    std::unique_ptr<Voxel> t_voxel{nullptr};
    std::unique_ptr<Shader> t_shader{ nullptr };
    std::unique_ptr<BlockDataManager> t_blockDataManager{nullptr};


    RenderData _renderData;

    std::unique_ptr<Camera> _camera{nullptr};

    


    // window Management : input
    // this assumes that there will be only one window for the application
    // that is the game window.
    inline static bool _keys[1024] = {};

    inline static bool _mouseFirstMoved = true;

    inline static float _lastMouseX = 0.0f;
    inline static float _lastMouseY = 0.0f;

    inline static float _mouseXChange = 0.0f;
    inline static float _mouseYChange = 0.0f;

};
