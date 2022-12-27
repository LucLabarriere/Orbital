#pragma once

#ifdef _WIN32

#ifdef FPSDEMOSCRIPTS_EXPORT 
#define FPSDEMOSCRIPTS_API __declspec(dllexport)
#else
#define FPSDEMOSCRIPTS_API __declspec(dllimport)
#endif

#else

#ifdef FPSDEMOSCRIPTS_EXPORT
#define FPSDEMOSCRIPTS_API
#else
#define FPSDEMOSCRIPTS_API
#endif

#endif

#include "OrbitalEngine/ECS/Components.h"

#include "OrbitalTools/Time.h"
#include "OrbitalTools/Random.h"
#include "OrbitalTools/Chrono.h"
