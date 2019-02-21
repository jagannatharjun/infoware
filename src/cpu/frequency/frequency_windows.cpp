// infoware - C++ System information Library
//
// Written in 2017 by nabijaczleweli <nabijaczleweli@gmail.com> and ThePhD <phdofthehouse@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>


#ifdef _WIN32


#include "infoware/cpu.hpp"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


std::int64_t iware::cpu::frequency() noexcept {
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return static_cast<int64_t>(freq.QuadPart * 1000);
}

// Use Query Performance Counter to get a nice accurate time-stamp.
__int64 GetQPCTime()
{
    LARGE_INTEGER qpcTime;
    QueryPerformanceCounter(&qpcTime);
    return qpcTime.QuadPart;
}

// Use QueryPerformanceCounter to interpret the results of GetQPCTime()
__int64 GetQPCRate()
{
    LARGE_INTEGER qpcRate;
    QueryPerformanceFrequency(&qpcRate);
    return qpcRate.QuadPart;
}

std::int64_t iware::cpu::max_frequency() noexcept {
	__int64 rdtscStart = __rdtsc();
	__int64 qpcStart = GetQPCTime();
	DWORD startTick = GetTickCount();
  const DWORD msDuration = 1000;
  const double qpcRate = (double)GetQPCRate();
	for (;;)
	{
			DWORD tickDuration = GetTickCount() - startTick;
			if (tickDuration >= msDuration)
					break;
	}
	__int64 rdtscElapsed = __rdtsc() - rdtscStart;
	__int64 qpcElapsed = GetQPCTime() - qpcStart;
	return rdtscElapsed / (qpcElapsed / qpcRate);
}

#endif
