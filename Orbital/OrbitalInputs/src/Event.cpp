#include "OrbitalInputs/Event.h"

namespace Orbital
{
	template <typename T>
	std::function<bool(T& e)> EventSlot<T>::sSlot = [](T& e) { return false; };

	template <typename T>
	void EventSlot<T>::Connect(std::function<bool(T& e)> slot)
	{
		sSlot = slot;
	}

	template <typename T>
	auto EventSlot<T>::OnEvent(T& e) -> bool
	{
		return sSlot(e);
	}

	template class EventSlot<KeyPressedEvent>;
	template class EventSlot<KeyReleasedEvent>;
	template class EventSlot<MouseMoveEvent>;
	template class EventSlot<MouseButtonPressedEvent>;
	template class EventSlot<MouseButtonReleasedEvent>;
	template class EventSlot<MouseScrolledEvent>;
} // namespace Orbital
