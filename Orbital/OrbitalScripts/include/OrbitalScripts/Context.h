#pragma once

#ifdef _WIN32

#ifdef ORBITAL_SCRIPTS_EXPORT 
#define ORBITAL_SCRIPTS_API __declspec(dllexport)
#else
#define ORBITAL_SCRIPTS_API __declspec(dllimport)
#endif

#else

#ifdef ORBITAL_SCRIPTS_EXPORT
#define ORBITAL_SCRIPTS_API
#else
#define ORBITAL_SCRIPTS_API
#endif

#endif

#include "OrbitalEngine/ECS/Components.h"

#include "OrbitalTools/Time.h"
#include "OrbitalTools/Random.h"
#include "OrbitalTools/Chrono.h"
