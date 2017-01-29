#pragma once
#include "PhysicsEntity.h"


namespace Atlas
{
	class Cube : public PhysicsEntity
	{
	public:
		Cube(float size, float x, float y, float z, unsigned int shaderProgramID);

		virtual void InitData();
	};
}