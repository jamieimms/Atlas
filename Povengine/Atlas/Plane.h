#pragma once
#include "BaseEntity.h"

namespace Atlas
{
	class Plane : public BaseEntity
	{
	public:
		Plane(float size, float x, float y, float z, unsigned int shaderProgramID);

		virtual void InitData();
	};
}