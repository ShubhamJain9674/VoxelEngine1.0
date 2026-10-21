#pragma once
#include <chrono>


namespace TimeManager
{
	// Get time since app start in milliseconds.
	inline double GetTimeMs()
	{
		using namespace std::chrono;
		
		static const steady_clock::time_point init = steady_clock::now();
		
		const auto t2 = steady_clock::now();

		const auto timeSpan = duration<double,std::milli>(t2 - init);
		
		return timeSpan.count();
	}

	// get time since app start in seconds.
	inline double GetTimeS()
	{
		return GetTimeMs() / 1000;
	}

};