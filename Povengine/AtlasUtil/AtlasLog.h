#pragma once
#include <fstream>
#include <mutex>
#include "AtlasString.h"


namespace AtlasUtil
{
	class AtlasLog
	{
	public:
		AtlasLog(AtlasString outputFileName, bool truncate, int maxSizeMiB);
		~AtlasLog();

		void Debug(const AtlasString& message);
		void Error(const AtlasString& message);

		bool IsInitialised() { return _isInitialised; }

	private:

		void Initialise(bool truncate);

		void Cleanup();

		void Log(const AtlasString& message);

		AtlasString _outputFileName;

		std::wofstream* _outFile;

		bool _isInitialised;

		unsigned int _maxSizeBytes;
		//

		std::mutex _outputMutex;

	};
}