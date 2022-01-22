#pragma once
#include <string>
namespace Clock {
#ifdef _WINDOWS
	typedef long long TimePoint;
#else
	typedef std::chrono::steady_clock::time_point TimePoint;
#endif
	TimePoint Now();
	double Duration(TimePoint from, TimePoint to);
	double DurationMs(TimePoint from, TimePoint to);
	double DurationUs(TimePoint from, TimePoint to);
	void Start();
	double End();
	double EndMs();
	double EndUs();
	std::string PrintDuration(double duration);
}
