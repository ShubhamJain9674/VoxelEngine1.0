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

    _camera = std::make_unique<Camera>(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            -90.0f,
            0.0f,
            5.0f,
            0.5f
        );

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


    // this data needs to be updated by objects for now its set to 1.
    // for each object based on position rotation scale etc appropriate transformation 
    // matrices need to be multiplied.
    _renderData.model = glm::mat4(1.0f);
    
    
    _renderData.model = glm::translate(
        _renderData.model,
        glm::vec3(0.0f, 0.0f, -3.0f)
    );

    angle += 0.1;
    if (angle > 360.0f)
        angle = 0.0f;


    _renderData.model = glm::rotate(
        _renderData.model,
        glm::radians(angle),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );



    // needs to be set once 
    // TODO  move this to init 
    // mostly set once . if window adjusted then the projection needs to be updated.
    // learn projection math : https://www.songho.ca/opengl/gl_projectionmatrix.html
    
    _renderData.projection = glm::perspective(glm::radians(_fov),
                                    GetAspectRatio(),
                                    _nearClip,
                                    _farClip
                                );
    
    

    _renderData.view = _camera->CalculateViewMatrix();
    t_shader->UseShader();
    t_shader->UpdateUniformData(_renderData);


    if (t_voxel)
    {
        t_voxel->DrawVoxel();
    }

    glfwSwapBuffers(_window);
}

float App::GetAspectRatio()
{
    int bufferWidth;
    int bufferHeight;

    glfwGetFramebufferSize(_window, &bufferWidth, &bufferHeight);
    return ((float)bufferWidth) / ((float)bufferHeight);
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