#pragma once
#include <ctime>

namespace AtlasUtil
{
	// Defines a timer that can be set to trigger after an interval. A callback is called when the timer elapses. This occurs on a different thread.
	class AtlasTimer
	{
	public:
		AtlasTimer(unsigned int interval) {}
		~AtlasTimer() {}

		void Start() {}
		void Stop() {}

		bool IsRunning() {}

	private:

		unsigned int _interval;
		bool _running;



		// Callback

	};
}