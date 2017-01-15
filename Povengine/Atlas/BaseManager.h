#pragma once
#include "..\AtlasUtil\AtlasLog.h"

namespace Atlas
{
	class BaseManager
	{
	public:
		BaseManager() : _initialised(false) {}
		virtual ~BaseManager() {}

	protected:

		AtlasUtil::AtlasLog* _log;


		bool _initialised;
	};
}