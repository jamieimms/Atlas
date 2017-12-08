#pragma once
#include "BaseEntity.h"

namespace Atlas
{
	class Sphere : public BaseEntity
	{
	public:
		Sphere(int segments, int rings, float size, float x, float y, float z, Shader* shader);

		virtual void InitData();

	private:
		int _segs;
		int _rings;
	};
}