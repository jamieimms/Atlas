#pragma once
#include "PhysicsEntity.h"


namespace Atlas
{
	class Cube : public PhysicsEntity
	{
	public:
		Cube(float size, glm::vec3 pos, Shader* shader);
		virtual ~Cube();

		virtual void InitData();
	};
}