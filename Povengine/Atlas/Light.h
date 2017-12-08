#pragma once
#include "PhysicsEntity.h"

namespace Atlas
{
	class Light : public PhysicsEntity
	{
	public:

		Light(float r, float g, float b, float brightness, Shader* shader);
		virtual ~Light();

		virtual void InitData();

	private:

		glm::vec3 _lightColour;

	};
}