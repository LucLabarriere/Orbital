#pragma once
#include "OrbitalTools/Context.h"
#include "OrbitalTools/Logger.h"

namespace Orbital
{
	template <typename T, typename E>
	using Expected = nonstd::expected<T, E>;

	template <typename E>
	auto MakeUnexpected(E&& value)
		-> decltype(nonstd::make_unexpected<E>(std::forward<E>(value)))
	{
		return nonstd::make_unexpected<E>(value);
	}

	template <typename T>
	using Option = std::optional<T>;

	struct Error
	{
		int type;
		std::string message;

		auto report() -> int
		{
			Logger::Error(message);

#ifdef ORBITAL_DEV
			Logger::Error("Stacktrace:");
			backward::StackTrace st;
			st.load_here(32);
			backward::Printer p;
			p.print(st);
#endif
			return type;
		}
	};

	enum class CommonErrors
	{
		Unknown = 1
	};

	struct UnknownError : public Error
	{
		UnknownError()
			: Error({ .type = (int)CommonErrors::Unknown,
					  .message = "Something went wrong" }){};
	};
} // namespace Orbital

namespace std
{
	inline auto operator<<(ostream& os, const Orbital::Error& e) -> ostream&
	{
		os << e.message;
		return os;
	}
} // namespace std

namespace Orbital
{

	inline void Assert(bool condition, const std::string& message)
	{
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
	}

	inline void Raise(const std::string& message)
	{
		Logger::Critical("Critical error");
		Logger::Critical(message);
		Logger::Critical("Stacktrace:");

		backward::StackTrace st;
		st.load_here(32);
		backward::Printer p;
		p.print(st);
		raise(SIGSEGV);
	}
} // namespace Orbital
