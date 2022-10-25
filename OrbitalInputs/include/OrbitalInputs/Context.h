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

#ifdef OINPUTS_GLFW
	#define GLFW_INCLUDE_NONE
    #include <GLFW/glfw3.h>
#endif

#include <functional>
#include <string>
