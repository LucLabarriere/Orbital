#pragma once

#include "OrbitalTools/Context.h"

namespace Orbital
{
    class OTOOLS_API Files
    {
    public:
        static const std::string& GetBinaryDir();
        static std::string GetAbsolutePath(const std::string& relativePath);
        static void SetBinaryDir(char* argv0);

    private:
        static inline std::string sBinaryDir = "";
    };
}
