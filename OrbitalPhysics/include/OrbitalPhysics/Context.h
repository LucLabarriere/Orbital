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
#include <map>
#include <vector>
#include <functional>

#include "OrbitalTools/Errors.h"
#include "OrbitalTools/Pointers.h"
#include "OrbitalTools/Logger.h"
#include "OrbitalTools/UUID.h"
#include "OrbitalTools/Maths.h"
#include "OrbitalTools/Time.h"
