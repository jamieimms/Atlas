#pragma once
#include "..\AtlasUtil\AtlasLog.h"

namespace Atlas
{
	class BaseManager
	{
	public:
		BaseManager(AtlasUtil::AtlasLog* log) : _initialised(false), _log(log) {}
		virtual ~BaseManager() {}

	protected:

		AtlasUtil::AtlasLog* _log;


		bool _initialised;
	};
}