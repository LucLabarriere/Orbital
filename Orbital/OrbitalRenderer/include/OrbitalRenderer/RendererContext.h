#pragma once

// OPENGL
#ifdef ORBITAL_RENDERER_OPENGL

#ifdef ORBITAL_RENDERER_DEBUG
#define GLAD_DEBUG
#endif

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#endif
