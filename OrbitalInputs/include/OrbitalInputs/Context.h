#pragma once

#ifdef _WIN32

#ifdef OINPUTS_EXPORT
#define OINPUTS_API __declspec(dllexport)
#else
#define OINPUTS_API __declspec(dllimport)
#endif

#else
#define OINPUTS_API
#endif 

#ifdef OINPUTS_OPENGL
#include <GLFW/glfw3.h>
#endif

#include <functional>
#include <string>
