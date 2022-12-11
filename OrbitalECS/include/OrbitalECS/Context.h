#pragma once

#ifdef _WIN32

#ifdef OECS_EXPORT
#define OECS_API __declspec(dllexport)
#else
#define OECS_API __declspec(dllimport)
#endif

#else
#define OECS_API
#endif 

#include <unordered_map>
#include <unordered_set>
#include <assert.h>

#include "OrbitalTools/Logger.h"
#include "OrbitalTools/UUID.h"
