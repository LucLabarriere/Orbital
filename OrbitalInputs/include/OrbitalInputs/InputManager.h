#pragma once

#include "OrbitalInputs/Context.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalLogger/Logger.h"

namespace Orbital
{
    class OINPUTS_API InputManager
    {
    public:
        void initializeInputManager();

        template <typename T>
        bool dispatchEvent(Event& e) // TODO move in cpp and do template specialization
        {
            if (e.getType() == T::GetType())
            {
                return EventSlot<T>::OnEvent(*(T*)&e);
            }
            return false;
        }

        virtual void onEvent(Event& e)
        {
            if (dispatchEvent<KeyPressedEvent>(e)) return;
            if (dispatchEvent<KeyReleasedEvent>(e)) return;
            if (dispatchEvent<MouseMoveEvent>(e)) return;
            if (dispatchEvent<MouseButtonPressedEvent>(e)) return;
            if (dispatchEvent<MouseButtonReleasedEvent>(e)) return;
            if (dispatchEvent<MouseScrolledEvent>(e)) return;
        }

        virtual bool onKeyPressed(KeyPressedEvent& e) { return false; }
        virtual bool onKeyReleased(KeyReleasedEvent& e) { return false; }
        virtual bool onMouseMove(MouseMoveEvent& e) { return false; }
        virtual bool onMouseButtonPressed(MouseButtonPressedEvent& e) { return false; }
        virtual bool onMouseButtonReleased(MouseButtonReleasedEvent& e) { return false; }
        virtual bool onMouseScrolled(MouseScrolledEvent& e) { return false; }
    };
}
