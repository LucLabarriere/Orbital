#include "OrbitalTools/Random.h"
#include <random>

namespace Orbital
{
	std::random_device Random::sDevice = std::random_device();
	std::mt19937_64 Random::sEngine = std::mt19937_64(Random::sDevice());
	std::uniform_int_distribution<uint64_t> Random::sUniformDistribution = std::uniform_int_distribution<uint64_t>();

	double Random::Get()
	{
		return (float)sUniformDistribution(Random::sEngine) / (float)sUniformDistribution.max();
	}
} // namespace Orbital
