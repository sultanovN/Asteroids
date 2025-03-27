#pragma once
#include <chrono>

//how timer works
// in a loop
//if (DidTimerEnd(startTime))
//{
//    doStuff
//    StartTimer(startTime);
//}

inline void StartTimer(std::chrono::steady_clock::time_point& startTime)
{
    startTime = std::chrono::steady_clock::now();
}

inline bool DidTimerEnd(const std::chrono::steady_clock::time_point& startTime, const std::chrono::milliseconds time)
{
    using namespace std::chrono_literals;
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime) >= time)
    {
        return true;
    }
    return false;
}