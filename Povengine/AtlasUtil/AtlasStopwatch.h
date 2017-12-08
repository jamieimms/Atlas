#pragma once
#include <chrono>

namespace AtlasUtil
{
	// Defines a timer that can be set to trigger after an interval. A callback is called when the timer elapses.
	class AtlasStopwatch
	{
	public:
		AtlasStopwatch();

		void Start();
		void Stop();
		void Reset();	

		double GetElapsedMs();
		double GetElapsedSec();

		bool IsRunning() { return _running; }

	private:
		bool _running;

		std::chrono::duration<double> GetElapsedDuration();

		std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;

		std::chrono::duration<double> _totalElapsed;


	};
}