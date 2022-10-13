#pragma once

#ifdef _WIN32
    #ifdef OESCRIPTS_EXPORT
    #define OESCRIPTS_API __declspec(dllexport)
    #else
    #define OESCRIPTS_API __declspec(dllimport)
    #endif
#else
    #define OESCRIPTS_API
#endif

