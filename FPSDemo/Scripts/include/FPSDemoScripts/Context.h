#pragma once

#ifdef _WIN32

#ifdef FPSDEMO_SCRIPTS_EXPORT 
#define FPSDEMO_SCRIPTS_API __declspec(dllexport)
#else
#define FPSDEMO_SCRIPTS_API __declspec(dllimport)
#endif

#else

#ifdef FPSDEMO_SCRIPTS_EXPORT
#define FPSDEMO_SCRIPTS_API
#else
#define FPSDEMO_SCRIPTS_API
#endif

#endif

#include "FPSDemoLibrary/Context.h"
