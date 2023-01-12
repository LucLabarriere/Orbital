#include "OrbitalEngine/Graphics/ShaderProgram.h"
#include "OrbitalTools/Files.h"

namespace Orbital
{
	ShaderProgram::ShaderProgram()
	{
	}

	void ShaderProgram::initialize(std::string_view vsPath, std::string_view fsPath)
	{
		mVsPath = vsPath;
		mFsPath = fsPath;
		Logger::Debug("ShaderProgram: Loading ", vsPath, ", ", fsPath);

		const std::string vsSource = Files::Content(vsPath);
		const std::string fsSource = Files::Content(fsPath);

		mCreatedTimeCountVS = Files::Timestamp(vsPath);
		mCreatedTimeCountFS = Files::Timestamp(fsPath);

		mShader = Shader::Create(vsSource, fsSource);
	}

	void ShaderProgram::terminate()
	{
		delete mShader;
	}

	ShaderProgram::~ShaderProgram()
	{
	}

	void ShaderProgram::bind() const
	{
		mShader->bind();
	}

	void ShaderProgram::mapUniformLocation(Uniform uniform, std::string_view uniformName)
	{
		mUniformLocations[uniform] = mShader->getUniformLocation(uniformName);
	}
} // namespace Orbital
