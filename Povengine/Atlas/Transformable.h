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
		Transformable(glm::vec4 pos);

		void SetUniformScale(float scale);
		void SetScale(float x, float y, float z);
		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float t, float z);		

		void SetRenderTransform(unsigned int transformLoc);

	private:
		glm::vec4 _pos;
		glm::mat4 _transMat;
		glm::vec3 _scale;
		glm::vec3 _rot;

	};
}