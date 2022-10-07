#pragma once
#include "OrbitalTools/Context.h"

namespace Orbital
{
    class OTOOLS_API Time
    {
    public:
        Time();
        Time(float seconds);
        Time(const Time& other);
        
        inline float microSeconds() const { return (float)mMicroSeconds; }
        inline float milliSeconds() const { return (float)mMicroSeconds / 1000.0f; }
        inline float seconds() const { return (float)mMicroSeconds / 1000000.0f; }

        Time operator+(const Time& other) const { return Time((float)(mMicroSeconds + other.mMicroSeconds) / 1000000.0f); }
        Time operator-(const Time& other) const { return Time((float)(mMicroSeconds - other.mMicroSeconds) / 1000000.0f); }

    private:
        int32_t mMicroSeconds;
    };
}

