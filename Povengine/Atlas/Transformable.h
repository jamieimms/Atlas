#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace Atlas
{

	class Transformable
	{
	public:

		Transformable(float x, float y, float z);
		Transformable(glm::vec3 pos);

		void SetUniformScale(float scale);
		void SetScale(float x, float y, float z);
		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float t, float z);

		glm::mat4 GetTransform();
		glm::vec3 GetPosition();

		void SetTransform(glm::mat4 newTransform);


	private:
		void UpdateTransform();

		glm::vec3 _pos;
		glm::mat4 _transMat;
		glm::vec3 _scale;
		glm::vec3 _rot;

		bool _requiresUpdate;

	};
};