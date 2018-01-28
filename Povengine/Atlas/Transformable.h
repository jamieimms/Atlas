#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "AtlasObject.h"

namespace Atlas
{

	class Transformable : public AtlasObject
	{
	public:

		Transformable(float x, float y, float z);
		Transformable(glm::vec3 pos);

		void SetUniformScale(float scale);
		void SetScale(float x, float y, float z);
		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3 pos);
		void SetRotation(float x, float y, float z);

		glm::mat4 GetTransform();
		glm::vec3 GetPosition();

		void SetTransform(glm::mat4 newTransform);

		float GetScaleX() { return _scale.x; }
		float GetScaleY() { return _scale.y; }
		float GetScaleZ() { return _scale.z; }

	private:
		void UpdateTransform();

		glm::vec3 _pos;
		glm::mat4 _transMat;
		glm::vec3 _scale;
		glm::vec3 _rot;

		bool _requiresUpdate;

	};
};