#pragma once

#include "OrbitalInputs/Context.h"
#include "OrbitalTools/Maths.h"

namespace Orbital
{
	/**
	 * @class Inputs
	 * @brief A static class that provides functions to query the state of inputs
	 */
	class ORBITAL_INPUTS_API Inputs
	{
	public:
		static auto GetMousePosition() -> Maths::Vec2;
		static auto GetScreenSpaceMousePosition() -> Maths::Vec2;
		static auto GetMouseDrag() -> Maths::Vec2;
		static auto IsKeyDown(int key) -> bool;
		static auto IsMouseButtonDown(int button) -> bool;
		static void SetContext(void* context);
		static void RegisterMouseEvents(bool value);
		static void RegisterKeyboardEvents(bool value);
		static void UpdateDrag();

	private:
		static inline void* mContext = nullptr;
	};
} // namespace Orbital
