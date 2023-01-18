#pragma once
#include "OrbitalTools/Context.h"

namespace Orbital
{
	class ORBITAL_TOOLS_API Time
	{
	public:
		Time();
		Time(float seconds);
		Time(const Time& other) = default;

		[[nodiscard]] auto microSeconds() const -> float
		{
			return (float)mMicroSeconds;
		}

		[[nodiscard]] auto milliSeconds() const -> float
		{
			return (float)mMicroSeconds / 1000.0f;
		}

		[[nodiscard]] auto seconds() const -> float
		{
			return (float)mMicroSeconds / 1000000.0f;
		}

		auto operator=(const Time& other) -> Time& = default;
		auto operator+(const Time& other) const -> Time
		{
			return { (float)(mMicroSeconds + other.mMicroSeconds) / 1000000.0f };
		}

		auto operator+=(const Time& other) -> Time&
		{
			mMicroSeconds += other.mMicroSeconds;
			return *this;
		}

		auto operator-(const Time& other) const -> Time
		{
			return { (float)(mMicroSeconds - other.mMicroSeconds) / 1000000.0f };
		}

	private:
		long mMicroSeconds;
	};
} // namespace Orbital
