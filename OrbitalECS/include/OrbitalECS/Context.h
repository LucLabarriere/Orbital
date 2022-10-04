#pragma once

#ifdef _WIN32
#ifdef OECS_LIBRARY
#define OECS_API __declspec(dllexport)
#else
#define OECS_API __declspec(dllimport)
#endif
#else
#define OECS_API
#endif 
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>
