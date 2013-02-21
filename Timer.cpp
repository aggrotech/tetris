#include "Timer.h"
#include <Windows.h>

Aggrotech::Timer::Timer()
    : delta(0.0f)
{
    __int64 countsPerSecond;

    QueryPerformanceFrequency((LARGE_INTEGER *) &countsPerSecond);
    secondsPerCount = 1.0 / static_cast<double>(countsPerSecond);

    QueryPerformanceCounter((LARGE_INTEGER *) &prevCount);
}

void Aggrotech::Timer::Tick()
{
    __int64 currentCount;
    QueryPerformanceCounter((LARGE_INTEGER *) &currentCount);

    __int64 countDelta = currentCount - prevCount;
    delta = static_cast<float>(countDelta * secondsPerCount);

    if (delta < 0.0f) {
        delta = 0.0f;
    }

    prevCount = currentCount;
}

float Aggrotech::Timer::GetDeltaSinceLastTick()
{
    return delta;
}
