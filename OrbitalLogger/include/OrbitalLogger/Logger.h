#pragma once
#include "OrbitalLogger/Context.h"

#define VAR(x) Orbital::Logger::Debug(#x, ": ", x);

namespace Orbital
{
    class Logger
    {
    public:
        template<class... Args>
        static void Debug(Args... args)
        {
            std::cout <<  FGGreen << "[Deb]" << Clear << ": ";
            (std::cout << ... << args);
            std::cout << "\n";
        }
        
        template<class... Args>
        static void Log(Args... args)
        {
            std::cout <<  FGBlue << "[Log]" << Clear << ": ";
            (std::cout << ... << args);
            std::cout << "\n";
        }

        template<class... Args>
        static void Error(Args... args)
        {
            std::cout << FGRed << "[Err]" << Clear << ": ";
            (std::cout << ... << args);
            std::cout << "\n";
        }

        static constexpr const char* FGBlue = "\033[1;34m";
        static constexpr const char* FGGreen = "\033[1;32m";
        static constexpr const char* FGCyan = "\033[1;36m";
        static constexpr const char* FGRed = "\033[1;33m";
        static constexpr const char* Underline = "\033[1;4m";

        static constexpr const char Clear[8] = "\033[0m";

    };
}
