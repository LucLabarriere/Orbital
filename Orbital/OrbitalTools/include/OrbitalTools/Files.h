#pragma once

#include "OrbitalTools/Context.h"

namespace Orbital
{
	class OTOOLS_API Files
	{
	public:
		static const std::string& GetBinaryDir();
		static std::string AbsolutePath(const std::string& relativePath);
		static bool Exists(const std::string& relativePath);
		static bool AbsoluteExists(const std::string& absolute);
		static void Copy(const std::string& relSource, const std::string& relDest);
		static void SetBinaryDir(char* argv0);
		static const std::string Content(const std::string& relativePath);
		static size_t Timestamp(const std::string& relativePath);

	private:
		static inline std::string sBinaryDir = "";
	};
} // namespace Orbital
