#include "OrbitalTools/UUID.h"
#include <random>

namespace Orbital
{
	std::random_device UUID::sDevice = std::random_device();
	std::mt19937_64 UUID::sEngine = std::mt19937_64(UUID::sDevice());
	std::uniform_int_distribution<uint64_t> UUID::sUniformDistribution = std::uniform_int_distribution<uint64_t>();

	auto UUID::getValue() const -> uint64_t
	{
		return mValue;
	}

	auto UUID::getHash() const -> size_t
	{
		return mHash;
	}
} // namespace Orbital
