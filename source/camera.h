#pragma once

#include "utility.h"
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{

public:
	Camera(glm::vec3 startPosition,
		glm::vec3 startUp,
		float startYaw,
		float startPitch,
		float startMoveSpeed,
		float startTurnSpeed);


	void MouseControl(float xChange, float yChange);
	void KeyControl(bool* keys, float DeltaTime);

	glm::mat4 CalculateViewMatrix();

	glm::vec3 GetCameraPosition();

private:
	void Update();

private:

	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	float _yaw;
	float _pitch;

	float _moveSpeed;
	float _turnSpeed;

};
