#include "camera.h"

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, 
	float startPitch, float startMoveSpeed, float startTurnSpeed)
	: _position(startPosition),_worldUp(startUp),_yaw(startYaw),_pitch(startPitch),
	  _front(glm::vec3(0.0f, 0.0f, -1.0f)),_moveSpeed(startMoveSpeed),_turnSpeed(startTurnSpeed)
{
	   
    Update();
}


void Camera::Update()
{
    _front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front.y = sin(glm::radians(_pitch));
    _front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(_front);

    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}

void Camera::MouseControl(float xChange, float yChange)
{
    xChange = xChange * _turnSpeed;
    yChange = yChange * _turnSpeed;

    _yaw += xChange;
    _pitch += yChange;

    if (_pitch > 89.0f)
    {
        _pitch = 89.0f;
    }

    if (_pitch < -89.0f)
    {
        _pitch = -89.0f;
    }
    Update();
}

void Camera::KeyControl(bool* keys, float DeltaTime)
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        _position += _front * _moveSpeed * DeltaTime;
    }
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        _position -= _front * _moveSpeed * DeltaTime;
    }
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        _position += _right * _moveSpeed * DeltaTime;
    }
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        _position -= _right * _moveSpeed * DeltaTime;
    }
}

glm::mat4 Camera::CalculateViewMatrix()
{
    return glm::lookAt(_position, _position + _front, _up);
}

glm::vec3 Camera::GetCameraPosition()
{
    return _position;
}
