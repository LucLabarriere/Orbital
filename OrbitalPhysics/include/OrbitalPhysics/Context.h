#pragma once

#ifdef _WIN32

#ifdef OPHYSICS_EXPORT
#define OPHYSICS_API __declspec(dllexport)
#else
#define OPHYSICS_API __declspec(dllimport)
#endif

#else
#define OPHYSICS_API
#endif 

#include "OrbitalLogger/Logger.h"
#include "OrbitalTools/Time.h"
#include "OrbitalTools/Maths.h"
