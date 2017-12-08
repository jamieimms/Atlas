#pragma once
#include <chrono>
#include "EntityHolder.h"
#include "..\AtlasUtil\AtlasStopwatch.h"

namespace Atlas
{
	class FiniteEntity : public EntityHolder
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