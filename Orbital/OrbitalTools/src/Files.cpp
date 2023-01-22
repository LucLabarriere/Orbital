#include "OrbitalTools/Files.h"
#include "OrbitalTools/Errors.h"
#include <cassert>
#include <filesystem>
#include <fstream>

namespace Orbital
{
	std::string Files::sBinaryDir = "";

	auto Files::GetBinaryDir() -> const std::string&
	{
		return sBinaryDir;
	}

	auto Files::AbsolutePath(std::string_view relativePath) -> std::string
	{
		return (std::filesystem::path(sBinaryDir) / std::filesystem::path(relativePath))
			.string();
	}

	auto Files::Exists(std::string_view relativePath) -> bool
	{
		return std::filesystem::exists(AbsolutePath(relativePath));
	}

	auto Files::AbsoluteExists(std::string_view absolutePath) -> bool
	{
		return std::filesystem::exists(absolutePath);
	}

	void Files::Copy(std::string_view relSource, std::string_view relDest)
	{
		std::filesystem::copy(AbsolutePath(relSource), AbsolutePath(relDest));
	}

	void Files::SetBinaryDir(char* argv0)
	{
		sBinaryDir = (std::filesystem::current_path() / std::filesystem::path(argv0))
						 .parent_path()
						 .string();
	}

	auto Files::Content(std::string_view relativePath) -> const std::string
	{
		std::string absolutePath = Files::AbsolutePath(relativePath);
		std::ifstream file;
		Orbital::Assert(
			Files::Exists(absolutePath), "File " + absolutePath + " does not exist"
		);
		file.open(absolutePath);

		std::stringstream fileContent;

		Orbital::Assert(file.is_open(), "Could not open file " + absolutePath);
		fileContent << file.rdbuf();

		return fileContent.str();
	}

	auto Files::Timestamp(std::string_view relativePath) -> size_t
	{
		return std::filesystem::last_write_time(Files::AbsolutePath(relativePath))
			.time_since_epoch()
			.count();
	}
} // namespace Orbital
