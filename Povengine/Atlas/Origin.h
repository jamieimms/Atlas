#pragma once
#include "BaseEntity.h"

namespace Atlas
{
	class Origin : public BaseEntity
	{
	public:
		Origin(float size, unsigned int shaderProgramID);
		virtual ~Origin();

		virtual void InitData();
	};
}