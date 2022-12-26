#pragma once

#ifdef _WIN32

#ifdef ORBITALSCRIPTS_EXPORT 
#define ORBITALSCRIPTS_API __declspec(dllexport)
#else
#define ORBITALSCRIPTS_API __declspec(dllimport)
#endif

#else

#ifdef ORBITALSCRIPTS_EXPORT
#define ORBITALSCRIPTS_API
#else
#define ORBITALSCRIPTS_API
#endif

#endif

#include "OrbitalEngine/ECS/Components.h"

#include "OrbitalTools/Time.h"
#include "OrbitalTools/Random.h"
#include "OrbitalTools/Chrono.h"
