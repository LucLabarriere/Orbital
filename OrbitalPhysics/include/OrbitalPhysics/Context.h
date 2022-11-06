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

#include <assert.h>
#include <memory>
#include <unordered_set>
#include <vector>
#include <functional>

#include "OrbitalLogger/Logger.h"
#include "OrbitalTools/Maths.h"
#include "OrbitalTools/Time.h"
