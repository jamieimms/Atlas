#pragma once
#include <fstream>
#include <mutex>

namespace AtlasUtil
{
	class AtlasLog
	{
	public:
		AtlasLog(std::wstring outputFileName, bool truncate, int maxSizeMiB);
		~AtlasLog();

		void Debug(const std::wstring& message);
		void Error(const std::wstring& message);

		bool IsInitialised() { return _isInitialised; }

	private:

		void Initialise(bool truncate);

		void Cleanup();

		void Log(const std::wstring& message);

		std::wstring _outputFileName;

		std::wofstream* _outFile;

		bool _isInitialised;

		unsigned int _maxSizeBytes;
		//

		std::mutex _outputMutex;

	};
}