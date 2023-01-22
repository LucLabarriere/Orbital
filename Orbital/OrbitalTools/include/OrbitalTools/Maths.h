#pragma once

#include "OrbitalTools/Context.h"

// TODO move everything to a cpp file so that glm does not get included everywhere ?
namespace Orbital
{
	namespace Maths
	{
		using Vec2 = glm::vec2;
		using Vec3 = glm::vec3;
		using Vec4 = glm::vec4;
		using Mat4 = glm::mat4;
		using Quaternion = glm::quat;
		static constexpr float PI = 3.14159265358979323846;

		static inline auto Orthographic(
			float x, float w, float y, float h, float clipMin, float clipMax
		) -> Mat4
		{
			return glm::ortho(x, w, y, h, clipMin, clipMax);
		}

		static inline auto Perspective(
			float radFov, float aspectRatio, float clipMin, float clipMax
		) -> Mat4
		{
			return glm::perspective(radFov, aspectRatio, clipMin, clipMax);
		}

		static inline auto Normalize(const Vec2& vec) -> Vec2
		{
			return glm::normalize(vec);
		}

		static inline auto Normalize(const Vec3& vec) -> Vec3
		{
			return glm::normalize(vec);
		}

		static inline auto Normalize(const Vec4& vec) -> Vec4
		{
			return glm::normalize(vec);
		}

		static inline auto Cross(const Vec3& vec1, const Vec3& vec2) -> Vec3
		{
			return glm::cross(vec1, vec2);
		}

		static inline auto LookAt(
			const Vec3& position, const Vec3& target, const Vec3& upDirection
		) -> Mat4
		{
			return glm::lookAt(position, target, upDirection);
		}

		static inline auto Rotate(const Mat4& mat, float radAngle, const Vec3& direction)
			-> Mat4
		{
			return glm::rotate(mat, radAngle, direction);
		}

		static inline auto Translate(const Mat4& mat, const Vec3& vec) -> Mat4
		{
			return glm::translate(mat, vec);
		}

		static inline auto Scale(const Mat4& mat, const Vec3& scale) -> Mat4
		{
			return glm::scale(mat, scale);
		}

		template <typename... Args>
		static inline auto Degree(Args&&... args)
			-> decltype(glm::degrees(std::forward<Args>(args)...))
		{
			return glm::degrees(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Radian(Args&&... args)
			-> decltype(glm::radians(std::forward<Args>(args)...))
		{
			return glm::radians(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Asin(Args&&... args)
			-> decltype(glm::asin(std::forward<Args>(args)...))
		{
			return glm::asin(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Acos(Args&&... args)
			-> decltype(glm::acos(std::forward<Args>(args)...))
		{
			return glm::acos(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Atan(Args&&... args)
			-> decltype(glm::atan(std::forward<Args>(args)...))
		{
			return glm::atan(std::forward<Args>(args)...);
		}

		static auto Atan2(float x, float y) -> float
		{
			return std::atan2(x, y);
		}

		static inline auto Sqrt(float value) -> float
		{
			return sqrt(value);
		}

		static inline auto Tan(float value) -> float
		{
			return tan(value);
		}

		static inline auto Cos(float value) -> float
		{
			return cos(value);
		}

		static inline auto Sin(float value) -> float
		{
			return sin(value);
		}

		static inline auto Round(float value) -> float
		{
			return round(value);
		}

		static inline auto Distance(const Maths::Vec3& c1, const Maths::Vec3& c2) -> float
		{
			return glm::distance(c1, c2);
		}

		static inline auto TripleProduct(const Maths::Vec3& c1, const Maths::Vec3& c2)
			-> Maths::Vec3
		{
			return Maths::Cross(Maths::Cross(c1, c2), c2);
		}

		template <typename... Args>
		static inline auto Magnitude(Args&&... args)
			-> decltype(glm::length(std::forward<Args>(args)...))
		{
			return glm::length(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Absolute(Args&&... args)
			-> decltype(glm::abs(std::forward<Args>(args)...))
		{
			return glm::abs(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Pow(Args&&... args)
			-> decltype(glm::pow(std::forward<Args>(args)...))
		{
			return glm::pow(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Dot(Args&&... args)
			-> decltype(glm::dot(std::forward<Args>(args)...))
		{
			return glm::dot(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Cross(Args&&... args)
			-> decltype(glm::cross(std::forward<Args>(args)...))
		{
			return glm::cross(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto LookAt(Args&&... args)
			-> decltype(glm::lookAt(std::forward<Args>(args)...))
		{
			return glm::lookAt(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto AngleAxis(Args&&... args)
			-> decltype(glm::angleAxis(std::forward<Args>(args)...))
		{
			return glm::angleAxis(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto EulerAngles(Args&&... args)
			-> decltype(glm::eulerAngles(std::forward<Args>(args)...))
		{
			return glm::eulerAngles(std::forward<Args>(args)...);
		}

		template <typename... Args>
		static inline auto Mat4Cast(Args&&... args)
			-> decltype(glm::mat4_cast(std::forward<Args>(args)...))
		{
			return glm::mat4_cast(std::forward<Args>(args)...);
		}
	} // namespace Maths
} // namespace Orbital

namespace std
{
	inline auto operator<<(ostream& os, const Orbital::Maths::Vec2& v) -> ostream&
	{
		os << v.x << ", " << v.y;
		return os;
	}
	inline auto operator<<(ostream& os, const Orbital::Maths::Vec3& v) -> ostream&
	{
		os << v.x << ", " << v.y << ", " << v.z;
		return os;
	}

	inline auto operator<<(ostream& os, const Orbital::Maths::Vec4& v) -> ostream&
	{
		os << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
		return os;
	}

	inline auto operator<<(ostream& os, const Orbital::Maths::Mat4& v) -> ostream&
	{
		os << "\n";
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				os << v[i][j] << " ";
			}
			os << "\n";
		}
		return os;
	}
} // namespace std
