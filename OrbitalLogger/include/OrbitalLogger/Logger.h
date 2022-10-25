#pragma once
#include "OrbitalLogger/Context.h"

#ifdef _WIN32
#define OFUNC_NAME() __FUNCTION__
#else
#define OFUNC_NAME() __PRETTY_FUNCTION__ 
#endif

#define LOGVAR(x) Orbital::Logger::Debug(#x, ": ", x)
#define LOGFUNC() Orbital::Logger::TraceFunction(OFUNC_NAME())

namespace Orbital
{
    class Logger
    {
    public:
        template<class... Args>
        static void Debug(Args... args)
        {
            #ifdef ODEBUG
            std::cout <<  FGGreen << "[Deb]" << Clear << ": ";
            (std::cout << ... << args);
            std::cout << "\n";
            #endif
        }
        
        template<class... Args>
        static void Log(Args... args)
        {
            std::cout <<  FGBlue << "[Log]" << Clear << ": ";
            (std::cout << ... << args);
            std::cout << "\n";
        }

        template<class... Args>
        static void Warning(Args... args)
        {
            std::cout <<  FGYellow << "[War]" << Clear << ": ";
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

        template<class... Args>
        static void Trace(Args... args)
        {
            #ifdef ODEBUG
            std::cout << FGCyan << "[Tra]" << Clear << ": ";
            (std::cout << ... << args);
            std::cout << "\n";
            #endif
        }

        template<class... Args>
        static void Critical(Args... args)
        {
            std::cout << FGRed << Underline << "[CRIT]" << ": ";
            (std::cout << ... << args);
            std::cout << Clear << "\n";
        }

        static void TraceFunction(const char* funcName)
        {
            Trace(funcName);
        }

        static constexpr const char* FGBlue = "\033[1;34m";
        static constexpr const char* FGGreen = "\033[1;32m";
        static constexpr const char* FGCyan = "\033[1;36m";
        static constexpr const char* FGRed = "\033[1;31m";
        static constexpr const char* FGYellow= "\033[1;33m";
        static constexpr const char* Underline = "\033[1;4m";
        static constexpr const char* Bold = "\033[1,1m]";

        static constexpr const char Clear[8] = "\033[0m";

    };
}
