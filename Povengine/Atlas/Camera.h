#pragma once
#include "Transformable.h"

namespace Atlas
{
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

		glm::vec3 _camPos;
		glm::vec3 _camTarget;

		glm::vec3 _camUp;
		glm::vec3 _upVec;
		glm::vec3 _rightVec;
		glm::vec3 _front;

		glm::mat4 _viewMat;

		float _yaw;
		float _pitch;

		bool _needsUpdate;
		bool _freeLook;
		float _speed;
	};
}