#include "AtlasStopwatch.h"

using namespace AtlasUtil;

AtlasStopwatch::AtlasStopwatch()
	: _running(false), _totalElapsed(0)
{
	_running = false;
}

void AtlasStopwatch::Start()
{
	if (_running) {
		return;
	}

	_startTime = std::chrono::high_resolution_clock::now();
	_running = true;
}

void AtlasStopwatch::Stop()
{
	if (!_running) {
		return;
	}

	_totalElapsed += std::chrono::high_resolution_clock::now() - _startTime;

	_running = false;
}

void AtlasStopwatch::Reset()
{
	_totalElapsed = std::chrono::duration<double>(0);
	_running = false;
}

void AtlasStopwatch::Restart()
{
	Reset();
	Start();
}

double AtlasStopwatch::GetElapsedMs()
{

	return std::chrono::duration_cast<std::chrono::milliseconds>(GetElapsedDuration()).count();
}

double AtlasStopwatch::GetElapsedSec()
{
	return std::chrono::duration_cast<std::chrono::seconds>(GetElapsedDuration()).count();
}

std::chrono::duration<double> AtlasStopwatch::GetElapsedDuration()
{
	if (!_running) {
		return _totalElapsed;
	}
	else {
		return (_totalElapsed + (std::chrono::high_resolution_clock::now() - _startTime));
	}
}