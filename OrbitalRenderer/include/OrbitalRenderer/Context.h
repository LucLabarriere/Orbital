
#pragma once

#ifdef _WIN32
#ifdef ORENDERER_EXPORT
#define ORENDERER_API __declspec(dllexport)
#else
#define ORENDERER_API __declspec(dllimport)
#endif
#else
#define ORENDERER_API
#endif 

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
