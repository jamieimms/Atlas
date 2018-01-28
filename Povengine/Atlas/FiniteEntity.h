#pragma once
#include <chrono>
#include "EntityInstance.h"
#include "..\AtlasUtil\AtlasStopwatch.h"

namespace Atlas
{
	class FiniteEntity : public EntityInstance
	{
	public:
		FiniteEntity(unsigned int lifeSeconds);
		virtual ~FiniteEntity();

		void Update();

	private:
		AtlasUtil::AtlasStopwatch _lifeTimer;

		unsigned int _lifeSeconds;
	};

}