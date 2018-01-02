#include "Camera.h"

using namespace Atlas;

Camera::Camera()
	:_speed(0.12f)
{
	_upVec = glm::vec3(0, 1.0f, 0);

	SetPosition(0, 1.0f, 2.0f);

	SetLookAt(0, 0, 0);

	Update();
}

void Camera::SetPosition(float x, float y, float z)
{
	_camPos = glm::vec3(x, y, z);
	_needsUpdate = true;
}

void Camera::SetLookAt(float x, float y, float z)
{
	_front = glm::vec3(x, y, z);
	_needsUpdate = true;
	_freeLook = false;
}

void Camera::SetAngle(float pitch, float yaw)
{
	_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	_front.y = sin(glm::radians(pitch));
	_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	_front = glm::normalize(_front);

	_front = _front;
	_needsUpdate = true;
	_freeLook = true;
}

void Camera::GetPitch(float& pitch)
{
	auto _camDirection = glm::normalize(_camPos - _camTarget);
	pitch = glm::degrees(asinf(_camDirection.y));
}

void Camera::GetYaw(float& yaw)
{
	auto _camDirection = glm::normalize(_camPos - _camTarget);
	yaw = glm::degrees(atan2f(_camDirection.x, _camDirection.z));
}

void Camera::Update()
{
	if (_needsUpdate) {
		//_camDirection = glm::normalize(_camPos - _camTarget);
		//_rightVec = glm::normalize(glm::cross(_upVec, _camDirection));
		//_camUp = glm::cross(_camDirection, _rightVec);
  		_viewMat = glm::lookAt(_camPos, _freeLook ? _camPos + _front : _front, _upVec);

		_needsUpdate = false;
	}
}

glm::vec3 Camera::GetPosition() const
{
	return _camPos;
}

glm::mat4 Camera::GetViewMatrix()
{
	Update();

	return _viewMat;
}

void Camera::MoveForward()
{
	Update();

	glm::vec3 forward(_viewMat[0][2], _viewMat[1][2], _viewMat[2][2]);

	_camPos += (-1.0f * forward) * _speed;
	_camTarget += (-1.0f * forward) * _speed;
	_needsUpdate = true;
}

void Camera::Backpedal()
{
	Update();

	glm::vec3 forward(_viewMat[0][2], _viewMat[1][2], _viewMat[2][2]);

	_camPos += (1.0f * forward) * _speed;
	_camTarget += (1.0f * forward) * _speed;
	_needsUpdate = true;
}

void Camera::Strafe(bool isLeft)
{
	float amt = isLeft ? -1.0f : 1.0f;
	Update();

	glm::vec3 strafe(_viewMat[0][0], _viewMat[1][0], _viewMat[2][0]);

	_camPos += (amt * strafe) * _speed;
	_camTarget += (amt * strafe) * _speed;
	_needsUpdate = true;
}