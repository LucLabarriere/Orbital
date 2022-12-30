#include "OrbitalTools/Errors.h"
#include "OrbitalTools/Files.h"
#include <assert.h>
#include <filesystem>
#include <fstream>

namespace Orbital
{
	const std::string& Files::GetBinaryDir()
	{
		return sBinaryDir;
	}

	std::string Files::GetAbsolutePath(const std::string& relativePath)
	{
		return (std::filesystem::path(sBinaryDir) / std::filesystem::path(relativePath)).string();
	}

	void Files::SetBinaryDir(char* argv0)
	{
		sBinaryDir = (std::filesystem::current_path() / std::filesystem::path(argv0)).parent_path().string();
	}
	const std::string Files::GetFileContent(const std::string& relativePath)
	{
		std::string absolutePath = Files::GetAbsolutePath(relativePath);
		std::ifstream file;
		Orbital::Assert(std::filesystem::exists(absolutePath), "File " + absolutePath + " does not exist");
		file.open(absolutePath);

		std::stringstream fileContent;

		Orbital::Assert(file.is_open(), "Could not open file " + absolutePath);
		fileContent << file.rdbuf();

		return fileContent.str();
	}

	size_t Files::GetFileModifiedTime(const std::string& relativePath)
	{
		return std::filesystem::last_write_time(Files::GetAbsolutePath(relativePath)).time_since_epoch().count();
	}
} // namespace Orbital
