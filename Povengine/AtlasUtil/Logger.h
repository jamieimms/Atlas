#pragma once
#include <fstream>

namespace AtlasUtil
{
	class Logger
	{
	public:
		Logger();
		~Logger();

		void Initialise();
		void Cleanup();
		
		void LogError();

	private:

		bool _isInitialised;
		//
	};
}