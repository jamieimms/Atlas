#pragma once

#include "BaseEntity.h"

namespace Atlas
{
	class Spawner : protected BaseEntity
	{

	public:
		Spawner(float x, float y, float z, unsigned int shaderProgramID);

		virtual void InitData();
	private:
		int _quality;
	};
}