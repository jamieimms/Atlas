#include "AtlasLog.h"
#include <sstream>
#include "AtlasTime.h"

using namespace AtlasUtil;

AtlasLog::AtlasLog(AtlasString outputFileName, bool truncate, int maxSizeMiB)
	:_isInitialised(false),_outputFileName(outputFileName), _outFile(nullptr)
{
	Initialise(truncate);
}

AtlasLog::~AtlasLog()
{
	Cleanup();
}

void AtlasLog::Initialise(bool truncate)
{
	_outFile = new std::wofstream(_outputFileName, truncate ? std::ios_base::trunc : std::ios_base::app);
	if (!_outFile->is_open()) {
		return;
	}

	_isInitialised = true;
}

void AtlasLog::Cleanup()
{
	if (_outFile != nullptr) {
		delete _outFile;
	}

	_isInitialised = false;
}

void AtlasLog::Debug(const AtlasString& message)
{
	// If not built in debug, this method should do nothing
//#ifdef debug
	if (!_isInitialised) {
		return;
	}

	AtlasString currentTime;
	AtlasTime::getCurrentTimeODBC(currentTime);
	
	std::wstringstream ss;
	ss << L"[" << currentTime << L" TID: " << std::this_thread::get_id() << L"] ";
	ss << L"DEBUG: ";
	ss << message;

	Log(ss.str());
//#endif
}

void AtlasLog::Error(const AtlasString& message)
{
	if (!_isInitialised) {
		return;
	}

	AtlasString currentTime;
	AtlasTime::getCurrentTimeODBC(currentTime);

	std::wstringstream ss;
	ss << L"[" << currentTime << L" TID: " << std::this_thread::get_id() << L"] ";
	ss << L"ERROR: ";
	ss << message;

	Log(ss.str());
}


void AtlasLog::Log(const AtlasString& message)
{
	std::lock_guard<std::mutex> lock(_outputMutex);

	(*_outFile) << message << std::endl;
	_outFile->flush();
}