#pragma once

#include "OrbitalRenderer/Containers.h"
#include "OrbitalRenderer/Context.h"
#include "OrbitalTools/Maths.h"

namespace Orbital
{
	class ORBITAL_RENDERER_API Shader
	{
	public:
		static auto Create(std::string_view vsSource, std::string_view fsSource)
			-> Shader*;
		virtual ~Shader() {}

		virtual void bind() const = 0;
		virtual auto getUniformLocation(std::string_view uniformName) const
			-> unsigned int = 0;

		virtual void setUniform1ui(unsigned int uniformLocation, unsigned int value)
			const = 0;
		virtual void setUniform1f(unsigned int uniformLocation, float value) const = 0;
		virtual void setUniform2f(unsigned int uniformLocation, const Maths::Vec2& vec)
			const = 0;
		virtual void setUniform3f(unsigned int uniformLocation, const Maths::Vec3& vec)
			const = 0;
		virtual void setUniform4f(unsigned int uniformLocation, const Maths::Vec4& vec)
			const = 0;
		virtual void setUniformMat4f(unsigned int uniformLocation, const Maths::Mat4& mat)
			const = 0;
	};
} // namespace Orbital
