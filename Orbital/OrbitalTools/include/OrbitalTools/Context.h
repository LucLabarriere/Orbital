#pragma once

#ifdef _WIN32
#ifdef ORBITAL_TOOLS_EXPORT
#define ORBITAL_TOOLS_API
#else
#define ORBITAL_TOOLS_API
#endif
#else
#define ORBITAL_TOOLS_API
#endif

#include <cmath>
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/matrix_transform.hpp>	 // glm::translate, glm::rotate, glm::scale
#include <glm/ext/scalar_constants.hpp>	 // glm::pi
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <random>

#include "OrbitalTools/vendor/Backtrace.h"
#include <nonstd/expected.hpp>

#define OE_UNCONST(Return_type, This, method)                                            \
	const_cast<Return_type>(const_cast<const This*>(this)->method())
