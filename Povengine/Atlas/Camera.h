#pragma once
#include <chrono>
#include "Transformable.h"

namespace Atlas
{
	const float CAM_MIN_SPEED = 0.01f;
	const float CAM_MOVE_FACTOR = 1.0f;
	const float DECEL_TIME_SEC = 0.05f;
	class Camera
	{
	public:
		Camera();
		void SetPosition(float x, float y, float z);
		void SetLookAt(float x, float y, float z);

		glm::mat4 GetViewMatrix();

		void MoveForward();
		void Backpedal();
		void Strafe(bool isLeft);
		void SetAngle(float pitch, float yaw);

		glm::vec3 GetPosition() const;
		void GetPitch(float& pitch);
		void GetYaw(float& yaw);

	private:

		void Update();
		void AdjustSpeed();

		glm::vec3 _camPos;
		glm::vec3 _camTarget;

		glm::vec3 _camUp;
		glm::vec3 _upVec;
		glm::vec3 _rightVec;
		glm::vec3 _front;

		glm::mat4 _viewMat;

		float _yaw;
		float _pitch;

		bool _freeLook;

		bool _needsUpdate;
		float _topSpeed;
		float _currentStrafeSpeed;
		float _currentForwardSpeed;
		float _acceleration;	// Acceleration per second

		bool _strafeLeft;
		bool _strafeRight;
		bool _forward;
		bool _backpedal;

		std::chrono::time_point<std::chrono::high_resolution_clock> _lastUpdate;
		std::chrono::time_point<std::chrono::high_resolution_clock> _lastStrafe;
		std::chrono::time_point<std::chrono::high_resolution_clock> _lastForward;



	};
}