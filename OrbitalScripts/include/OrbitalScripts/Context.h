#pragma once

#ifdef OESCRIPTS_EXPORT
#    define OESCRIPTS_API __declspec(dllexport)
#else
#    define OESCRIPTS_API __declspec(dllimport)
#endif

#include "OrbitalEngine/Utils/Context.h"