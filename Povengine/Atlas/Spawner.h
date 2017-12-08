#pragma once

#include "BaseEntity.h"

namespace Atlas
{
	class Spawner : protected BaseEntity
	{

	public:
		Spawner(float x, float y, float z, Shader* shader);

		virtual void InitData();
	private:
		int _quality;
	};
}