#pragma once
#include "OrbitalLogger/Context.h"

namespace Orbital
{
    class Logger
    {
    public:
        template<class... Args>
        static void Log(Args... args)
        {
            std::cout << "\033[2K\r";
            std::cout <<  FGBlue << "[Log]" << Clear << ": ";
            (std::cout << ... << args);
            std::cout << std::flush;
        }

        template<class... Args>
        static void Error(Args... args)
        {
            std::cout << '\n';
            std::cout << FGRed << "[Err]" << Clear << ": ";
            (std::cout << ... << args);
        }

        static constexpr const char* FGBlue = "\033[1;34m";
        static constexpr const char* FGGreen = "\033[1;32m";
        static constexpr const char* FGCyan = "\033[1;36m";
        static constexpr const char* FGRed = "\033[1;33m";
        static constexpr const char* Underline = "\033[1;4m";

        static constexpr const char Clear[8] = "\033[0m";

    };
}
