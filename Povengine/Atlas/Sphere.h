#pragma once
#include "BaseEntity.h"

namespace Atlas
{
	class Sphere : public BaseEntity
	{
	public:
		Sphere(float size, float x, float y, float z, unsigned int shaderProgramID);

		virtual void InitData();
	};
}