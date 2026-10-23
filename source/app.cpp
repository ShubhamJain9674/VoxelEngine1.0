#include "app.h"




// TODO : switching to discrete GPU seems to be more work then it seems


internal void FramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    GLCall(glViewport(0, 0, width, height));
}

internal void CloseProgram(GLFWwindow* window)
{
    
    glfwSetWindowShouldClose(window, GL_TRUE); 
}


App::App()
{
}


bool App::Init()
{
    if (!glfwInit())
    {
        return false;
    }
    
    _window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME, NULL, NULL);

    if (!_window)
    {
        glfwTerminate();
        return false;
    }

    //TODO : understand this context versioning.
    //TODO : CHECK what happens if i use heigher version of opengl and glsl
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwMakeContextCurrent(_window);

    unsigned int err = glewInit();

    if (err != GLEW_OK)
    {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;        glfwTerminate();
        return false;
    }

    std::cout << "GLEW version : " << glewGetString(GLEW_VERSION)
        << std::endl;

    // framebuffer
    int fbwidth, fbheight;
    glfwGetFramebufferSize(_window, &fbwidth, &fbheight);

    GLCall(glViewport(0, 0,fbwidth,fbheight));

    // callbacks setup
    glfwSetFramebufferSizeCallback(_window, FramebufferResizeCallback);

    glfwSetWindowCloseCallback(_window, CloseProgram);

    glfwSwapInterval(1);

    // TEMP
    t_voxel = std::make_unique<Voxel>();
    t_voxel->Init();


    t_shader = std::make_unique<Shader>("shaders/vertex.shader", "shaders/fragment.shader");



    return true;
}

void App::Run()
{
    while (!glfwWindowShouldClose(_window))
    {
        double now = TimeManager::GetTimeS();
        _deltaTime = now - _lastTime;
        _lastTime = now;

        _timeElapsed += _deltaTime;

        if (_timeElapsed >= FRAME_DELTA)
        {
            _timeElapsed -= FRAME_DELTA;
            Update(FRAME_DELTA);
        }

        Render();

    }
}




/*DeltaTime in s.*/
void App::Update(double DeltaTime)
{
    glfwPollEvents();

}


void App::Render()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

    if (t_voxel)
    {
        t_voxel->DrawVoxel(t_shader.get());
    }

    glfwSwapBuffers(_window);
}

void App::Cleanup()
{
    glfwTerminate();
    
    // cleanup resources
}


App::~App()
{
    Cleanup();
}