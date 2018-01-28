#include "Camera.h"

using namespace Atlas;

Camera::Camera()
	:_topSpeed(0.12f)
{
	_acceleration = 0.4f;
	_currentStrafeSpeed = 0.0f;
	_currentForwardSpeed = 0.0f;

	_forward = false;
	_backpedal = false;
	_strafeLeft = false;
	_strafeRight = false;

	_upVec = glm::vec3(0, 1.0f, 0);

	SetPosition(0, 1.0f, 2.0f);

	SetLookAt(0, 0, 0);

	_lastUpdate = std::chrono::high_resolution_clock::now();
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
	AdjustSpeed();

	if (_strafeLeft || _strafeRight) {
		float amt = _strafeLeft ? -CAM_MOVE_FACTOR : CAM_MOVE_FACTOR;

		glm::vec3 strafe(_viewMat[0][0], _viewMat[1][0], _viewMat[2][0]);

		_camPos += (amt * strafe) * _currentStrafeSpeed;
		_camTarget += (amt * strafe) * _currentStrafeSpeed;

		_needsUpdate = true;
	}
	if (_forward || _backpedal) {
		glm::vec3 forward(_viewMat[0][2], _viewMat[1][2], _viewMat[2][2]);

		float amt = _forward ? -CAM_MOVE_FACTOR : CAM_MOVE_FACTOR;

		_camPos += (amt * forward) * _currentForwardSpeed;
		_camTarget += (amt * forward) * _currentForwardSpeed;
		_needsUpdate = true;
	}
	
	if (_needsUpdate) {
		//_camDirection = glm::normalize(_camPos - _camTarget);
		//_rightVec = glm::normalize(glm::cross(_upVec, _camDirection));
		//_camUp = glm::cross(_camDirection, _rightVec);
  		_viewMat = glm::lookAt(_camPos, _freeLook ? _camPos + _front : _front, _upVec);

		_needsUpdate = false;
		_lastUpdate = std::chrono::high_resolution_clock::now();
	}
}

void Camera::AdjustSpeed()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> elapsedSec = now - _lastUpdate;
	std::chrono::duration<float> strafeDecel = now - _lastStrafe;
	std::chrono::duration<float> fwdDecel = now - _lastForward;

	bool isStrafeOver = false;
	if (_strafeLeft || _strafeRight) {
		if (strafeDecel.count() >= DECEL_TIME_SEC && _currentStrafeSpeed > CAM_MIN_SPEED) {
			isStrafeOver = true;
		}

		if (isStrafeOver) {
			_currentStrafeSpeed -= (_acceleration * elapsedSec.count());
			if (_currentStrafeSpeed <= CAM_MIN_SPEED) {
				_currentStrafeSpeed = CAM_MIN_SPEED;
				_strafeLeft = false;
				_strafeRight = false;
			}
		}
		else {
			// Accelerate
			_currentStrafeSpeed += (_acceleration * elapsedSec.count());
			if (_currentStrafeSpeed > _topSpeed) {
				_currentStrafeSpeed = _topSpeed;
			}
		}
	}

	bool isFwdOver = false;
	if (_forward || _backpedal) {
		if (fwdDecel.count() >= DECEL_TIME_SEC && _currentForwardSpeed > CAM_MIN_SPEED) {
			isFwdOver = true;
		}

		if (isFwdOver) {
			_currentForwardSpeed -= (_acceleration * elapsedSec.count());
			if (_currentForwardSpeed <= CAM_MIN_SPEED) {
				_currentForwardSpeed = CAM_MIN_SPEED;
				_forward = false;
				_backpedal = false;
			}
		}
		else {
			// Accelerate
			_currentForwardSpeed += (_acceleration * elapsedSec.count());
			if (_currentForwardSpeed > _topSpeed) {
				_currentForwardSpeed = _topSpeed;
			}
		}
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

/// <summary>
/// Move the camera forwards relative to its current angle
/// </summary>
void Camera::MoveForward()
{

	_forward = true;
	_backpedal = false;
	_lastForward = std::chrono::high_resolution_clock::now();

	//_activeMove = true;
	//Update();

	//glm::vec3 forward(_viewMat[0][2], _viewMat[1][2], _viewMat[2][2]);

	//_camPos += (-CAM_MOVE_FACTOR * forward) * _currentSpeed;
	//_camTarget += (-CAM_MOVE_FACTOR * forward) * _currentSpeed;
	//_needsUpdate = true;
}

/// <summary>
/// Move the camera backwards relative to its current angle
/// </summary>
void Camera::Backpedal()
{
	_backpedal = true;
	_forward = false;
	_lastForward = std::chrono::high_resolution_clock::now();

	//_activeMove = true;
	//Update();

	//glm::vec3 forward(_viewMat[0][2], _viewMat[1][2], _viewMat[2][2]);

	//_camPos += (CAM_MOVE_FACTOR * forward) * _currentSpeed;
	//_camTarget += (CAM_MOVE_FACTOR * forward) * _currentSpeed;
	//_needsUpdate = true;
}

/// <summary>
/// Move the camera left or right relative to its current position and angle
/// </summary>
void Camera::Strafe(bool isLeft)
{
	if (isLeft) {
		_strafeLeft = true;	
		_strafeRight = false;
	}
	else {
		_strafeRight = true;
		_strafeLeft = false;
	}

	_lastStrafe = std::chrono::high_resolution_clock::now();
}