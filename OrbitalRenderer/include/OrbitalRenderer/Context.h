
#pragma once

#ifdef _WIN32
#ifdef ORENDERER_LIBRARY
#define ORENDERER_API __declspec(dllexport)
#else
#define ORENDERER_API __declspec(dllimport)
#endif
#else
#define ORENDERER_API
#endif 

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
