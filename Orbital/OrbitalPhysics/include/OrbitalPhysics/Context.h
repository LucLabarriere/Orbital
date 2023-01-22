#pragma once

#ifdef _WIN32

#ifdef ORBITAL_PHYSICS_EXPORT
#define ORBITAL_PHYSICS_API __declspec(dllexport)
#else
#define ORBITAL_PHYSICS_API __declspec(dllimport)
#endif

#else
#define ORBITAL_PHYSICS_API
#endif

#include <assert.h>
#include <functional>
#include <map>
#include <memory>
#include <unordered_set>
#include <vector>

#include "OrbitalTools/Errors.h"
#include "OrbitalTools/Logger.h"
#include "OrbitalTools/Maths.h"
#include "OrbitalTools/Pointers.h"
#include "OrbitalTools/Time.h"
#include "OrbitalTools/UUID.h"
