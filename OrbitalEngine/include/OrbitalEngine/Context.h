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
