#include "AtlasLog.h"
#include <sstream>
#include "..\AtlasAPI\AtlasAPIHelper.h"

using namespace AtlasUtil;
using namespace std;

AtlasLog::AtlasLog(string outputFileName, bool truncate, int maxSizeMiB)
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
	_outFile = new std::ofstream(_outputFileName, truncate ? std::ios_base::trunc : std::ios_base::app);
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

void AtlasLog::Debug(const string& message)
{
	// If not built in debug, this method should do nothing?
//#ifdef debug
	if (!_isInitialised) {
		return;
	}
	
	std::stringstream ss;
	ss << "[" << AtlasAPI::AtlasAPIHelper::GetCurrentTimeODBC() << " TID: " << std::this_thread::get_id() << "] ";
	ss << "DEBUG: ";
	ss << message;

	Log(ss.str());
//#endif
}

void AtlasLog::Error(const string& message)
{
	if (!_isInitialised) {
		return;
	}

	std::stringstream ss;
	ss << "[" << AtlasAPI::AtlasAPIHelper::GetCurrentTimeODBC() << " TID: " << std::this_thread::get_id() << "] ";
	ss << "ERROR: ";
	ss << message;

	Log(ss.str());
}


void AtlasLog::Log(const string& message)
{
	std::lock_guard<std::mutex> lock(_outputMutex);

	(*_outFile) << message << std::endl;
	_outFile->flush();
}