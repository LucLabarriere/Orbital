#pragma once

#ifdef _WIN32

#ifdef ORBITAL_ECS_EXPORT
#define ORBITAL_ECS_API __declspec(dllexport)
#else
#define ORBITAL_ECS_API __declspec(dllimport)
#endif

#else
#define ORBITAL_ECS_API
#endif 

#include <csignal>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "OrbitalTools/Errors.h"
#include "OrbitalTools/Logger.h"
#include "OrbitalTools/UUID.h"
