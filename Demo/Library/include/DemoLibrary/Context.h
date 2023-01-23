#pragma once

#ifdef _WIN32

#ifdef DEMO_LIB_EXPORT
#define DEMO_LIB_API __declspec(dllexport)
#else
#define DEMO_LIB_API __declspec(dllimport)
#endif

#else
#define DEMO_LIB_API
#endif

#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalInputs/Core.h"
#include "OrbitalTools/Time.h"
#include "OrbitalTools/Random.h"
#include "OrbitalTools/Chrono.h"
#include "OrbitalTools/Errors.h"
#include "OrbitalTools/Pointers.h"
