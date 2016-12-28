#pragma once
#include <fstream>
#include <mutex>

namespace AtlasUtil
{
	class AtlasLog
	{
	public:
		AtlasLog(std::string outputFileName, bool truncate, int maxSizeMiB);
		~AtlasLog();

		void Debug(const std::string& message);
		void Error(const std::string& message);

		bool IsInitialised() { return _isInitialised; }

	private:

		void Initialise(bool truncate);

		void Cleanup();

		void Log(const std::string& message);

		std::string _outputFileName;

		std::ofstream* _outFile;

		bool _isInitialised;

		unsigned int _maxSizeBytes;
		//

		std::mutex _outputMutex;

	};
}