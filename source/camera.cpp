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

glm::mat4 Camera::CalculateViewMatrix()
{
    return glm::lookAt(_position, _position + _front, _up);
}

glm::vec3 Camera::GetCameraPosition()
{
    return _position;
}
