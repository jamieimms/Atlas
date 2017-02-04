#pragma once
#include "PhysicsEntity.h"

namespace Atlas
{
	class Light : public PhysicsEntity
	{
	public:

		Light(float r, float g, float b, float brightness, unsigned int shaderProgramID);
		virtual ~Light();

		virtual void InitData();

	private:

		glm::vec3 _lightColour;

	};
}