#pragma once

#include "OrbitalTools/Context.h"

namespace Orbital
{
	class OTOOLS_API UUID
	{
	public:
		UUID()
			: mValue(sUniformDistribution(sEngine))
			, mHash(std::hash<uint64_t>()(mValue))
		{

		}

		UUID(uint64_t value)
			: mValue(value)
			, mHash(std::hash<uint64_t>()(mValue))
		{
		}

		UUID Copy() const
		{
			return UUID(*this);
		}

		static inline UUID Null() { return UUID(0); }
		uint64_t GetValue() const { return mValue; }
		size_t GetHash() const { return mHash; }
		operator uint64_t() const { return mValue; }

	private:
		uint64_t mValue;
		size_t mHash;

        static std::random_device sDevice;
        static std::mt19937_64 sEngine;
        static std::uniform_int_distribution<uint64_t> sUniformDistribution;
	};
}

namespace std
{
	template <>
	struct hash<Orbital::UUID>
	{
		size_t operator()(const Orbital::UUID& uuid) const
		{
			return uuid.GetHash();
		}
	};
}
