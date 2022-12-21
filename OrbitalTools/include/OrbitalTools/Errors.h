#pragma once
#include "OrbitalTools/Context.h"
#include "OrbitalTools/Logger.h"

namespace Orbital
{
	inline void Assert(bool condition, const std::string& message)
	{
#ifdef OENGINE_DEBUG
		if (!condition)
		{
			Logger::Critical("Assertion failed");
			Logger::Critical(message);
			Logger::Critical("Stacktrace:");

			backward::StackTrace st;
			st.load_here(32);
			backward::Printer p;
			p.print(st);
			raise(SIGSEGV);
		}
#endif
	}
}
