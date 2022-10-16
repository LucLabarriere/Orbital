#include "OrbitalTools/Random.h"
#include <random>

namespace Orbital
{
    auto Random::sDevice = std::random_device();
    auto Random::sEngine = std::mt19937_64(Random::sDevice());
	auto Random::sUniformDistribution = std::uniform_int_distribution<uint64_t>();


    double Random::Get()
    {
        return (float)sUniformDistribution(Random::sEngine) / (float)sUniformDistribution.max();
    }
}
