#pragma once

#include <memory>

namespace Orbital
{
	template <typename T>
	using Ref = std::shared_ptr<T>;
	template <typename T>
	using Unique = std::unique_ptr<T>;
	template <typename T>
	using WeakRef = std::weak_ptr<T>;

	template <typename T, typename... Args>
	static inline auto MakeRef(Args&&... args) -> decltype(std::make_shared<T>(std::forward<Args>(args)...))
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename... Args>
	static inline auto MakeUnique(Args&&... args) -> decltype(std::make_unique<T>(std::forward<Args>(args)...))
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
} // namespace Orbital
