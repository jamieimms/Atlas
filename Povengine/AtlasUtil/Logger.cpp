#include "Logger.h"

using namespace AtlasUtil;

Logger::Logger()
	:_isInitialised(false)
{
	Initialise();
}

Logger::~Logger()
{
	Cleanup();
}

void Logger::Initialise()
{
	_isInitialised = true;
}

void Logger::Cleanup()
{
	_isInitialised = false;
}

void Logger::LogError()
{
	//Stub
}