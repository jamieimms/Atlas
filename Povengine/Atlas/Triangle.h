#pragma once
#include "BaseEntity.h"

namespace Atlas
{
	class Triangle : public BaseEntity
	{
	public:
		Triangle(float size, float x, float y, float z, Shader* shader);

		virtual void InitData();
	};
}