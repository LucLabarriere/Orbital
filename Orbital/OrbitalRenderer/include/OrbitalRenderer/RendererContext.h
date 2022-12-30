#pragma once

// OPENGL
#ifdef ORENDERER_OPENGL

#ifdef ORENDERER_DEBUG
#define GLAD_DEBUG
#endif

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#endif
