#pragma once

#ifdef _WIN32

#ifdef FPSDEMOLIB_EXPORT
#define FPSDEMOLIB_API __declspec(dllexport)
#else
#define FPSDEMOLIB_API __declspec(dllimport)
#endif

#else
#define FPSDEMOLIB_API
#endif

#include "OrbitalEngine/ECS/Components.h"
#include "OrbitalInputs/Core.h"
#include "OrbitalTools/Time.h"
#include "OrbitalTools/Random.h"
#include "OrbitalTools/Chrono.h"
#include "OrbitalTools/Errors.h"
#include "OrbitalTools/Pointers.h"
