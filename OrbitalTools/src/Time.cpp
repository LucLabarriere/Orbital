#include "OrbitalTools/Time.h"
#include <bits/chrono.h>
#include <ratio>

namespace Orbital
{
    Time::Time()
        : mMicroSeconds(std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
        ).count())
    {

    }

    Time::Time(float seconds)
        : mMicroSeconds((int32_t)(seconds * 1000000))
    {

    }

    Time::Time(const Time& other)
        : mMicroSeconds(other.mMicroSeconds)
    {

    }
}
