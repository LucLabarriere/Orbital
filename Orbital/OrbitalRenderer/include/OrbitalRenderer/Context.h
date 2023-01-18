#pragma once

#ifdef _WIN32
#ifdef ORBITAL_RENDERER_EXPORT
#define ORBITAL_RENDERER_API __declspec(dllexport)
#else
#define ORBITAL_RENDERER_API __declspec(dllimport)
#endif

#else
#define ORBITAL_RENDERER_API
#endif 

#include <cassert>
#include <string>
#include <stdlib.h>
#include <functional>
