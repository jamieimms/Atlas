#pragma once
#include "BaseEntity.h"

namespace Atlas
{
	class Origin : public BaseEntity
	{
	public:
		Origin(float size, Shader* shader);
		virtual ~Origin();

		virtual void InitData();
	};
}