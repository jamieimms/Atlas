#pragma once
#include "BaseEntity.h"

namespace Atlas
{
	class Cone : public BaseEntity
	{
	public:
		Cone(int quality, float size, glm::vec3 pos, unsigned int shaderProgramID);

		virtual void InitData();
	private:
		int _quality;
	};
}