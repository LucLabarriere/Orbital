#pragma once

#include "OrbitalTools/Context.h"

namespace Orbital
{
	class ORBITAL_TOOLS_API Files
	{
	public:
		static auto GetBinaryDir() -> const std::string&;
		static auto AbsolutePath(std::string_view relativePath) -> std::string;
		static auto Exists(std::string_view relativePath) -> bool;
		static auto AbsoluteExists(std::string_view absolute) -> bool;
		static void Copy(std::string_view relSource, std::string_view relDest);
		static void SetBinaryDir(char* argv0);
		static auto Content(std::string_view relativePath) -> const std::string;
		static auto Timestamp(std::string_view relativePath) -> size_t;

	private:
		static std::string sBinaryDir;
	};
} // namespace Orbital
