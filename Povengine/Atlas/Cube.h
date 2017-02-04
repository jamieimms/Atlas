#pragma once
#include "PhysicsEntity.h"


namespace Atlas
{
	class Cube : public PhysicsEntity
	{
	public:
		Cube(float size, glm::vec3 pos, unsigned int shaderProgramID);
		virtual ~Cube();

		virtual void InitData();
	};
}