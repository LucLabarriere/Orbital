#pragma once

#include "OrbitalInputs/Context.h"
#include "OrbitalInputs/Event.h"
#include "OrbitalLogger/Logger.h"

namespace Orbital
{
    /**
     * @class InputManager
     * @brief Base interface class for the input handling system
     * 
     * Make your application class inherit from it:
     * `class Application : public InputManager`
     * And call the `initializeInputManager` function after you created
     * a GLFW window and set the context
     *
     * It has a virtual `onEvent` method that dispatches events in the most
     * simplest way possible. You can override this method for more complex
     * behaviours
     *
     * Override the `onKeyPressed`, `onKeyReleased`, etc. methods to match your
     * needs.
     */
    class OINPUTS_API InputManager
    {
    public:
        /**
         * @brief Initializing function, call it after you've set a GLFW context
         */
        void initializeInputManager(void* context);

        /**
         * @brief dispatches the event of type T
         *
         * @tparam T The actual event type (KeyPressedEvent, etc.)
         * @param e The event to dispatch
         * @return bool true if the event was handled, false otherwise
         */
        template <typename T>
        bool dispatchEvent(Event& e) // TODO move in cpp and do template specialization
        {
            if (e.getType() == T::GetType())
            {
                return EventSlot<T>::OnEvent(*(T*)&e);
            }
            return false;
        }

        /**
         * @brief the callback that is called by the input API (GLFW)
         *
         * The default method is quite simple, override it for a more complex behaviour
         * For example:
         * ```
         * for (auto& state : mGameStates)
         * {
         *     if (dispatchEvent<KeyPressedEvent>(e)) return;
         *     if (dispatchEvent<KeyReleased>(e)) return;
         * }
         * for (auto& state : mEditorStates)
         * {
         *     if (dispatchEvent<MouseMoveEvent>(e)) return;
         *     if (dispatchEvent<MouseButtonPressedEvent(e)) return;
         *     if (dispatchEvent<MouseButtonReleasedEvent(e)) return;
         * }
         *
         * In this example, only the key events are captured in game mode
         * Whereas the editor catches the mouse events
         * ```
         *
         * @param e the event to handle
         */
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

        void pollEvents();
    };
}
