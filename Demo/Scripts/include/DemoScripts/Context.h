#pragma once

#ifdef _WIN32

#ifdef DEMOSCRIPTS_EXPORT 
#define DEMOSCRIPTS_API __declspec(dllexport)
#else
#define DEMOSCRIPTS_API __declspec(dllimport)
#endif

#else

#ifdef DEMOSCRIPTS_EXPORT
#define DEMOSCRIPTS_API
#else
#define DEMOSCRIPTS_API
#endif
#endif

#include "DemoLibrary/Context.h"
