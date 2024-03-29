#pragma once

#include "OrbitalEngine/Context.h"

#include "OrbitalRenderer/Shader.h"

namespace Orbital
{
	enum Uniform
	{
		Model = 0,
		View,
		Color,
		Radius,
	};

	class ORBITAL_ENGINE_API ShaderProgram
	{
	public:
		using UniformLocationMap = std::unordered_map<Uniform, unsigned int>;

	public:
		ShaderProgram();
		~ShaderProgram();

		void initialize(std::string_view vsPath, std::string_view fsPath);
		void terminate();
		void bind() const;
		void mapUniformLocation(Uniform uniform, std::string_view uniformName);

		template <typename T>
		void setUniform(Uniform uniform, const T& value) const;

		inline auto getCreatedTimeCountVS() const -> size_t
		{
			return mCreatedTimeCountVS;
		}
		inline auto getCreatedTimeCountFS() const -> size_t
		{
			return mCreatedTimeCountFS;
		}
		inline auto getVsPath() const -> std::string_view { return mVsPath; }
		inline auto getFsPath() const -> std::string_view { return mFsPath; }

	private:
		Shader* mShader = nullptr;
		UniformLocationMap mUniformLocations;
		size_t mCreatedTimeCountVS = 0;
		size_t mCreatedTimeCountFS = 0;
		std::string mVsPath = "";
		std::string mFsPath = "";
	};

	template <> // Unsigned int
	inline void ShaderProgram::setUniform<unsigned int>(
		Uniform uniform, const unsigned int& value
	) const
	{
		mShader->setUniform1ui(mUniformLocations.at(uniform), value);
	}

	template <> // Float
	inline void ShaderProgram::setUniform<float>(Uniform uniform, const float& value)
		const
	{
		mShader->setUniform1f(mUniformLocations.at(uniform), value);
	}

	template <> //  Vec2
	inline void ShaderProgram::setUniform<Maths::Vec2>(
		Uniform uniform, const Maths::Vec2& value
	) const
	{
		mShader->setUniform2f(mUniformLocations.at(uniform), value);
	}

	template <> // Vec3
	inline void ShaderProgram::setUniform<Maths::Vec3>(
		Uniform uniform, const Maths::Vec3& value
	) const
	{
		mShader->setUniform3f(mUniformLocations.at(uniform), value);
	}

	template <> // Vec4
	inline void ShaderProgram::setUniform<Maths::Vec4>(
		Uniform uniform, const Maths::Vec4& value
	) const
	{
		mShader->setUniform4f(mUniformLocations.at(uniform), value);
	}

	template <> // Mat4
	inline void ShaderProgram::setUniform<Maths::Mat4>(
		Uniform uniform, const Maths::Mat4& value
	) const
	{
		mShader->setUniformMat4f(mUniformLocations.at(uniform), value);
	}
} // namespace Orbital
