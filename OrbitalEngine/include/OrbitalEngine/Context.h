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

#include "OrbitalTools/Pointers.h"
#include "OrbitalTools/Logger.h"
#include "OrbitalTools/Maths.h"
#include "OrbitalTools/Time.h"
#include "OrbitalTools/UUID.h"

namespace Orbital
{
	using EntityID = UUID;
}
