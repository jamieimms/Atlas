#pragma once
#include "BaseEntity.h"

namespace Atlas
{
	class Cube : public BaseEntity
	{
	public:
		Cube(float size, float x, float y, float z, unsigned int shaderProgramID);

		virtual void InitData();
	};
}