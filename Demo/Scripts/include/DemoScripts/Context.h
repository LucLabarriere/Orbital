#pragma once

#ifdef _WIN32

#ifdef DEMO_SCRIPTS_EXPORT 
#define DEMO_SCRIPTS_API __declspec(dllexport)
#else
#define DEMO_SCRIPTS_API __declspec(dllimport)
#endif

#else

#ifdef DEMO_SCRIPTS_EXPORT
#define DEMO_SCRIPTS_API
#else
#define DEMO_SCRIPTS_API
#endif
#endif

#include "DemoLibrary/Context.h"
