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

#include <stdlib.h>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "OrbitalTools/Time.h"
#include "OrbitalLogger/Logger.h"
