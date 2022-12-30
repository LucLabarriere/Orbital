#pragma once

#include "glm/trigonometric.hpp"
#include <cmath>
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/matrix_transform.hpp>	 // glm::translate, glm::rotate, glm::scale
#include <glm/ext/scalar_constants.hpp>	 // glm::pi
#include <glm/mat4x4.hpp>				 // glm::mat4
#include <glm/vec3.hpp>					 // glm::vec3
#include <glm/vec4.hpp>					 // glm::vec4
#include <math.h>

// TODO move everything to a cpp file so that glm does not get included everywhere ?
namespace Orbital
{
	namespace Maths
	{
		using Vec2 = glm::vec2;
		using Vec3 = glm::vec3;
		using Vec4 = glm::vec4;
		using Mat4 = glm::mat4;

		static inline Mat4 Orthographic(float x, float w, float y, float h, float clipMin, float clipMax)
		{
			return glm::ortho(x, w, y, h, clipMin, clipMax);
		}

		static inline Mat4 Perspective(float radFov, float aspectRatio, float clipMin, float clipMax)
		{
			return glm::perspective(radFov, aspectRatio, clipMin, clipMax);
		}

		static inline Vec2 Normalize(const Vec2& vec)
		{
			return glm::normalize(vec);
		}

		static inline Vec3 Normalize(const Vec3& vec)
		{
			return glm::normalize(vec);
		}

		static inline Vec4 Normalize(const Vec4& vec)
		{
			return glm::normalize(vec);
		}

		static inline Vec3 Cross(const Vec3& vec1, const Vec3& vec2)
		{
			return glm::cross(vec1, vec2);
		}

		static inline Mat4 LookAt(const Vec3& position, const Vec3& target, const Vec3& upDirection)
		{
			return glm::lookAt(position, target, upDirection);
		}

		static inline Mat4 Rotate(const Mat4& mat, float radAngle, const Vec3& direction)
		{
			return glm::rotate(mat, radAngle, direction);
		}

		static inline Mat4 Translate(const Mat4& mat, const Vec3& vec)
		{
			return glm::translate(mat, vec);
		}

		static inline Mat4 Scale(const Mat4& mat, const Vec3& scale)
		{
			return glm::scale(mat, scale);
		}

		static inline float Radian(float degree)
		{
			return glm::radians(degree);
		}

		static inline float Degree(float radian)
		{
			return glm::degrees(radian);
		}

		static inline float Sqrt(float value)
		{
			return sqrt(value);
		}

		static inline float Tan(float value)
		{
			return tan(value);
		}

		static inline float Cos(float value)
		{
			return cos(value);
		}

		static inline float Sin(float value)
		{
			return sin(value);
		}

		static inline float Round(float value)
		{
			return round(value);
		}

		static inline float Distance(const Maths::Vec3& c1, const Maths::Vec3& c2)
		{
			return glm::distance(c1, c2);
		}

		static inline Maths::Vec3 TripleProduct(const Maths::Vec3& c1, const Maths::Vec3& c2)
		{
			return Maths::Cross(Maths::Cross(c1, c2), c2);
		}

		template <typename... Args>
		static inline auto Magnitude(Args&&... args) -> decltype(glm::length(std::forward<Args>(args)...))
		{
			return glm::length(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Absolute(Args&&... args) -> decltype(glm::abs(std::forward<Args>(args)...))
		{
			return glm::abs(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Pow(Args&&... args) -> decltype(glm::pow(std::forward<Args>(args)...))
		{
			return glm::pow(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Dot(Args&&... args) -> decltype(glm::dot(std::forward<Args>(args)...))
		{
			return glm::dot(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Cross(Args&&... args) -> decltype(glm::cross(std::forward<Args>(args)...))
		{
			return glm::cross(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto LookAt(Args&&... args) -> decltype(glm::lookAt(std::forward<Args>(args)...))
		{
			return glm::lookAt(std::forward<Args>(args)...);
		}


	} // namespace Maths
} // namespace Orbital
