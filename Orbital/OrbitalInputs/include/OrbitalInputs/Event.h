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
		Event()
		{
		}

		EventType getType() const
		{
			return mType;
		}

	protected:
		EventType mType = EventType::BaseEvent;
	};

	class KeyEvent : public Event
	{
	public:
		KeyEvent(int key) : Event(), mKey(key)
		{
		}

		int getKey() const
		{
			return mKey;
		}

	private:
		int mKey;
	};

	class OINPUTS_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int key) : KeyEvent(key)
		{
			mType = EventType::KeyPressed;
		}

		static inline EventType GetType()
		{
			return EventType::KeyPressed;
		}
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int key) : KeyEvent(key)
		{
			mType = EventType::KeyReleased;
		}

		static inline EventType GetType()
		{
			return EventType::KeyReleased;
		}
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float xPos, float yPos) : Event(), mX(xPos), mY(yPos)
		{
			mType = EventType::MouseMove;
		}

		float getX() const
		{
			return mX;
		}
		float getY() const
		{
			return mY;
		}

		static inline EventType GetType()
		{
			return EventType::MouseMove;
		}

	private:
		float mX;
		float mY;
	};

	class MouseButtonEvent : public MouseMoveEvent
	{
	public:
		MouseButtonEvent(float xPos, float yPos, int btn) : MouseMoveEvent(xPos, yPos), mButton(btn)
		{
		}

		int getButton() const
		{
			return mButton;
		}

	private:
		int mButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(float xPos, float yPos, int btn) : MouseButtonEvent(xPos, yPos, btn)
		{
			mType = EventType::MouseButtonPressed;
		}

		static inline EventType GetType()
		{
			return EventType::MouseButtonPressed;
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(float xPos, float yPos, int btn) : MouseButtonEvent(xPos, yPos, btn)
		{
			mType = EventType::MouseButtonReleased;
		}

		static inline EventType GetType()
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

		static inline EventType GetType()
		{
			return EventType::MouseScrolled;
		}

	private:
		float mXOffset;
		float mYOffset;
	};

	template <typename T>
	class OINPUTS_API EventSlot
	{
	public:
		static void Connect(std::function<bool(T& e)> slot);
		static bool OnEvent(T& e);

	private:
		static std::function<bool(T& e)> sSlot;
	};
} // namespace Orbital
