#pragma once

#ifdef OTOOLS_LIBRARY
#define OTOOLS_API __declspec(dllexport)
#else
#define OTOOLS_API __declspec(dllimport)
#endif

#include <random>
#include <iostream>
#include <chrono>