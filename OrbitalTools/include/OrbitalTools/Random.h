#pragma once

#include "OrbitalTools/Context.h"
#include "OrbitalTools/UUID.h"
#include <cstdlib>
#include <random>

namespace Orbital
{

    class OTOOLS_API Random
    {
    public:
        static double Get();

    private:
        static std::random_device sDevice;
        static std::mt19937_64 sEngine;
        static std::uniform_int_distribution<uint64_t> sUniformDistribution;
    };
}
