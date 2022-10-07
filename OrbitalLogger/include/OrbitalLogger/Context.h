#pragma once

#ifdef _WIN32
#ifdef OLOGGER_EXPORT
#define OLOGGER_API __declspec(dllexport)
#else
#define OLOGGER_API __declspec(dllimport)
#endif
#else
#define OLOGGER_API
#endif 

#include <string>
#include <iostream>
