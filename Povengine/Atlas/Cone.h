#pragma once
#include "BaseEntity.h"

namespace Atlas
{
	class Cone : public BaseEntity
	{
	public:
		Cone(float size, float x, float y, float z, unsigned int shaderProgramID);

		virtual void InitData();
		void SetVertex(int &dataPos, float x, float y, float z, float r, float g, float b);
		void SetIndex(int &indexPos, unsigned short a, unsigned short b, unsigned short c);
	};
}