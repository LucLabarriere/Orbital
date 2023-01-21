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
		static Maths::Vec2 GetMousePosition();
		static Maths::Vec2 GetScreenSpaceMousePosition();
		static Maths::Vec2 GetMouseDrag();
		static bool IsKeyDown(int key);
		static bool IsMouseButtonDown(int button);
		static void SetContext(void* context);
		static void RegisterMouseEvents(bool value);
		static void RegisterKeyboardEvents(bool value);
		static void UpdateDrag();

	private:
		static inline void* mContext = nullptr;
	};
} // namespace Orbital
