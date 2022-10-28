#pragma once

#ifdef _WIN32

#ifdef OENGINE_EXPORT
#define OENGINE_API __declspec(dllexport)
#else
#define OENGINE_API __declspec(dllimport)
#endif

#else
#define OENGINE_API
#endif

#include <functional>
#include <memory>
#include <stdlib.h>
#include <unordered_map>
#include <unordered_set>

#include "OrbitalECS/ECS.h"
#include "OrbitalLogger/Logger.h"
#include "OrbitalTools/Maths.h"
#include "OrbitalTools/Time.h"
