#pragma once

#ifdef _WIN32
#ifdef OTOOLS_EXPORT
#define OTOOLS_API __declspec(dllexport)
#else
#define OTOOLS_API __declspec(dllimport)
#endif
#else
#define OTOOLS_API
#endif

#include <random>
#include <chrono>
