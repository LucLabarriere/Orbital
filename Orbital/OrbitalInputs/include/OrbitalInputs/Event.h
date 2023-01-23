#pragma once

#include "OrbitalInputs/Context.h"

namespace Orbital
{
	enum EventType
	{
		BaseEvent,
		KeyPressed,
		KeyReleased,
		MouseMove,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseScrolled
	};

	class Event
	{
	public:
		Event() {}

		auto getType() const -> EventType { return mType; }

	protected:
		EventType mType = EventType::BaseEvent;
	};

	class KeyEvent : public Event
	{
	public:
		KeyEvent(int key) : Event(), mKey(key) {}

		auto getKey() const -> int { return mKey; }

	private:
		int mKey;
	};

	class ORBITAL_INPUTS_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int key) : KeyEvent(key) { mType = EventType::KeyPressed; }

		static inline auto GetType() -> EventType { return EventType::KeyPressed; }
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int key) : KeyEvent(key) { mType = EventType::KeyReleased; }

		static inline auto GetType() -> EventType { return EventType::KeyReleased; }
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float xPos, float yPos) : Event(), mX(xPos), mY(yPos)
		{
			mType = EventType::MouseMove;
		}

		auto getX() const -> float { return mX; }
		auto getY() const -> float { return mY; }

		static inline auto GetType() -> EventType { return EventType::MouseMove; }

	private:
		float mX;
		float mY;
	};

	class MouseButtonEvent : public MouseMoveEvent
	{
	public:
		MouseButtonEvent(float xPos, float yPos, int btn)
			: MouseMoveEvent(xPos, yPos), mButton(btn)
		{
		}

		auto getButton() const -> int { return mButton; }

	private:
		int mButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(float xPos, float yPos, int btn)
			: MouseButtonEvent(xPos, yPos, btn)
		{
			mType = EventType::MouseButtonPressed;
		}

		static inline auto GetType() -> EventType
		{
			return EventType::MouseButtonPressed;
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(float xPos, float yPos, int btn)
			: MouseButtonEvent(xPos, yPos, btn)
		{
			mType = EventType::MouseButtonReleased;
		}

		static inline auto GetType() -> EventType
		{
			return EventType::MouseButtonReleased;
		}
	};

	class MouseScrolledEvent : public MouseMoveEvent
	{
	public:
		MouseScrolledEvent(float xPos, float yPos, float xOffset, float yOffset)
			: MouseMoveEvent(xPos, yPos), mXOffset(xOffset), mYOffset(yOffset)
		{
			mType = EventType::MouseScrolled;
		}

		static inline auto GetType() -> EventType { return EventType::MouseScrolled; }

	private:
		float mXOffset;
		float mYOffset;
	};

	template <typename T>
	class ORBITAL_INPUTS_API EventSlot
	{
	public:
		static void Connect(std::function<bool(T& e)> slot);
		static auto OnEvent(T& e) -> bool;

	private:
		static std::function<bool(T& e)> sSlot;
	};
} // namespace Orbital
