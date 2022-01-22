#include "clock.h"
#include <cmath>
#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
namespace Clock {
#ifdef _WINDOWS
	TimePoint Now() { LARGE_INTEGER tp; QueryPerformanceCounter(&tp); return tp.QuadPart; }
	double Duration(TimePoint from, TimePoint to) {
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		return static_cast<double>(to - from) / frequency.QuadPart;
	}
#else
	TimePoint Now() { return std::chrono::steady_clock::now(); }
	double Duration(TimePoint from, TimePoint to) {
		return std::chrono::duration_cast<std::chrono::duration<double>>(to - from).count();
	}
#endif
	double DurationMs(TimePoint from, TimePoint to) { return Duration(from, to) * 1000; }
	double DurationUs(TimePoint from, TimePoint to) { return Duration(from, to) * 1000000; }
	thread_local TimePoint StartPoint;
	void Start() { StartPoint = Now(); }
	double End() { return Duration(StartPoint, Now()); }
	double EndMs() { return DurationMs(StartPoint, Now()); }
	double EndUs() { return DurationUs(StartPoint, Now()); }
	std::string PrintDuration(double duration) {
		char buf[] = "00.00.00:000";
		size_t hours = ((size_t)std::floor(duration / 3600)) % 24;
		size_t min = ((size_t)std::floor(duration / 60)) % 60;
		size_t sec = ((size_t)std::floor(duration)) % 60;
		size_t ms = ((size_t)std::round(duration * 1000)) % 1000;
#ifdef _WINDOWS
		sprintf_s(buf, 13, "%02d.%02d.%02d:%03d", hours, min, sec, ms);
#else
		sprintf(buf, "%02d.%02d.%02d:%03d", hours, min, sec, ms);
#endif
		return buf;
	}
}