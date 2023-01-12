#pragma once

#include "OrbitalRenderer/RendererContext.h"
#include "OrbitalRenderer/Shader.h"

namespace Orbital
{
	class ORENDERER_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* vsSource, const char* fsSource);
		virtual ~OpenGLShader() override;

		virtual void bind() const override;
		virtual unsigned int getUniformLocation(std::string_view uniformName) const override;

		virtual void setUniform1ui(unsigned int uniformLocation, unsigned int value) const override;
		virtual void setUniform1f(unsigned int uniformLocation, float value) const override;
		virtual void setUniform2f(unsigned int uniformLocation, const Maths::Vec2& vec) const override;
		virtual void setUniform3f(unsigned int uniformLocation, const Maths::Vec3& vec) const override;
		virtual void setUniform4f(unsigned int uniformLocation, const Maths::Vec4& vec) const override;
		virtual void setUniformMat4f(unsigned int uniformLocation, const Maths::Mat4& mat) const override;

	private:
		GLuint mRendererID = 0;
	};
} // namespace Orbital
