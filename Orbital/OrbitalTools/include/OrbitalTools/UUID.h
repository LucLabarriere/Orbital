#pragma once

#include "OrbitalTools/Context.h"

namespace Orbital
{
	class ORBITAL_TOOLS_API UUID
	{
	public:
		UUID() : mValue(sUniformDistribution(sEngine)), mHash(std::hash<uint64_t>()(mValue)){};
		UUID(uint64_t value) : mValue(value), mHash(std::hash<uint64_t>()(mValue)){};

		[[nodiscard]] auto Copy() const -> UUID
		{
			return { *this };
		}

		static auto Null() -> UUID
		{
			return { 0 };
		}

		[[nodiscard]] auto getValue() const -> uint64_t;
		[[nodiscard]] auto getHash() const -> size_t;
		operator uint64_t() const
		{
			return mValue;
		}

	private:
		uint64_t mValue;
		size_t mHash;

		static std::random_device sDevice;
		static std::mt19937_64 sEngine;
		static std::uniform_int_distribution<uint64_t> sUniformDistribution;
	};
} // namespace Orbital

namespace std
{
	template <>
	struct hash<Orbital::UUID>
	{
		auto operator()(const Orbital::UUID& uuid) const -> size_t
		{
			return uuid.getHash();
		}
	};
} // namespace std
