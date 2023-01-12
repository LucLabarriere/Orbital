#include "OrbitalTools/Files.h"
#include "OrbitalTools/Errors.h"
#include <assert.h>
#include <filesystem>
#include <fstream>

namespace Orbital
{
	const std::string& Files::GetBinaryDir()
	{
		return sBinaryDir;
	}

	std::string Files::AbsolutePath(std::string_view relativePath)
	{
		return (std::filesystem::path(sBinaryDir) / std::filesystem::path(relativePath)).string();
	}

	bool Files::Exists(std::string_view relativePath)
	{
		return std::filesystem::exists(AbsolutePath(relativePath));
	}

	bool Files::AbsoluteExists(std::string_view absolutePath)
	{
		return std::filesystem::exists(absolutePath);
	}

	void Files::Copy(std::string_view relSource, std::string_view relDest)
	{
		std::filesystem::copy(AbsolutePath(relSource), AbsolutePath(relDest));
	}

	void Files::SetBinaryDir(char* argv0)
	{
		sBinaryDir = (std::filesystem::current_path() / std::filesystem::path(argv0)).parent_path().string();
	}

	const std::string Files::Content(std::string_view relativePath)
	{
		std::string absolutePath = Files::AbsolutePath(relativePath);
		std::ifstream file;
		Orbital::Assert(Files::Exists(absolutePath), "File " + absolutePath + " does not exist");
		file.open(absolutePath);

		std::stringstream fileContent;

		Orbital::Assert(file.is_open(), "Could not open file " + absolutePath);
		fileContent << file.rdbuf();

		return fileContent.str();
	}

	size_t Files::Timestamp(std::string_view relativePath)
	{
		return std::filesystem::last_write_time(Files::AbsolutePath(relativePath)).time_since_epoch().count();
	}
} // namespace Orbital
