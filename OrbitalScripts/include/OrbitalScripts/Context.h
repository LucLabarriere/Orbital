#pragma once

#ifdef _WIN32 // TODO remove useless stuff here

#ifdef OSCRIPTS_EXPORT
#define OSCRIPTS_API __declspec(dllexport)
#else
#define OSCRIPTS_API __declspec(dllimport)
#endif

#else

#ifdef OSCRIPTS_EXPORT
#define OSCRIPTS_API
#else
#define OSCRIPTS_API
#endif

#endif

#include "OrbitalEngine/ECS/Components.h"
