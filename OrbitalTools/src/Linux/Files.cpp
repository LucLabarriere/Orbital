#ifndef _WIN32

#include "OrbitalTools/Files.h"
#include <filesystem>

namespace Orbital
{
    std::string Files::getPathToBinaryDirectory()
    {
        return std::filesystem::canonical("/proc/self/exe").parent_path();
    }
}

#endif
