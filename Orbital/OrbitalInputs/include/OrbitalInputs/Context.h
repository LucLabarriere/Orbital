#pragma once

#ifdef _WIN32
#ifdef ORBITAL_INPUTS_EXPORT
#define ORBITAL_INPUTS_API __declspec(dllexport)
#else
#define ORBITAL_INPUTS_API __declspec(dllimport)
#endif
#else
#define ORBITAL_INPUTS_API
#endif

#ifdef OINPUTS_GLFW
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#endif

#include <functional>
#include <string>
