#pragma once
#include "BaseEntity.h"

namespace Atlas
{
	class Cone : public BaseEntity
	{
	public:
		Cone(int quality, float size, glm::vec3 pos, Shader* shader);

		virtual void InitData();
	private:
		int _quality;
	};
}