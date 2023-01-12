#pragma once

#include "OrbitalTools/Context.h"

namespace Orbital
{
	class OTOOLS_API Files
	{
	public:
		static const std::string& GetBinaryDir();
		static std::string AbsolutePath(std::string_view relativePath);
		static bool Exists(std::string_view relativePath);
		static bool AbsoluteExists(std::string_view absolute);
		static void Copy(std::string_view relSource, std::string_view relDest);
		static void SetBinaryDir(char* argv0);
		static const std::string Content(std::string_view relativePath);
		static size_t Timestamp(std::string_view relativePath);

	private:
		static inline std::string sBinaryDir = "";
	};
} // namespace Orbital
