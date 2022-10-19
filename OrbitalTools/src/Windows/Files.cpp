#ifdef _WIN32

#include "OrbitalTools/Files.h"
#include <filesystem>
#include <windows.h>

namespace Orbital
{
    std::string Files::getPathToBinaryDirectory()
    {
        
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        return std::filesystem::path(buffer).parent_path().string();
    }
}

#endif
