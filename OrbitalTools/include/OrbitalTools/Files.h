#pragma once

#ifdef _WIN32
//TODO implement for windows
#else

#include <filesystem>

static inline std::string getPathToExecutable()
{
    return std::filesystem::canonical("/proc/self/exe");
}

static inline std::string getPathToBinaryDirectory()
{
    return std::filesystem::canonical("/proc/self/exe").parent_path();
}

#endif
