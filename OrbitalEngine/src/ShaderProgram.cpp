#include "OrbitalEngine/ShaderProgram.h"
#include "OrbitalTools/Files.h"

namespace Orbital
{
	ShaderProgram::ShaderProgram()
	{
	}

	void ShaderProgram::initialize(const std::string& vsPath, const std::string& fsPath)
	{
		mVsPath = vsPath;
		mFsPath = fsPath;

		const std::string vsSource = Files::GetFileContent(vsPath);
		const std::string fsSource = Files::GetFileContent(fsPath);

		mCreatedTimeCountVS = Files::GetFileModifiedTime(vsPath);
		mCreatedTimeCountFS = Files::GetFileModifiedTime(fsPath);

		mShader = Shader::Create(vsSource.c_str(), fsSource.c_str());
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

	void ShaderProgram::mapUniformLocation(Uniform uniform, const std::string& uniformName)
	{
		mUniformLocations[uniform] = mShader->getUniformLocation(uniformName);
	}
} // namespace Orbital
