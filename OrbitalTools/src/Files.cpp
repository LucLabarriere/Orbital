#include "OrbitalTools/Files.h"
#include <filesystem>

namespace Orbital
{
    const std::string& Files::GetBinaryDir()
    {
        return sBinaryDir;
    }

    std::string Files::GetAbsolutePath(const std::string& relativePath)
    {
        return (std::filesystem::path(sBinaryDir) / std::filesystem::path(relativePath)).string();
    }

    void Files::SetBinaryDir(char* argv0)
    {
        sBinaryDir = (
            std::filesystem::current_path() / std::filesystem::path(argv0)
        ).parent_path().string();
    }
}
