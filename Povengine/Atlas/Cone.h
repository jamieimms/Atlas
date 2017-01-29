#pragma once
#include "BaseEntity.h"

namespace Atlas
{
	class Cone : public BaseEntity
	{
	public:
		Cone(int quality, float size, float x, float y, float z, unsigned int shaderProgramID);

		virtual void InitData();
	private:
		int _quality;
	};
}