//
// Created by Peter Bone on 15/06/2020.
//

#ifndef SDLTEST_INPUTMANAGER_H
#define SDLTEST_INPUTMANAGER_H


#include <SDL_events.h>
#include <memory>
#include <map>
#include <set>
#include "Base.h"

namespace Engine {

    enum class InputKeyState {
        Pressed,
        Released,
        Moved
    };

    enum class InputKey {
        UNKNOWN,
        MouseButtonLeft,
        MouseButtonRight,
        Left,
        Right,
        Up,
        Down,
        Space,
        A,
        S,
        D,
        F
    };

    enum class InputDeviceType {
        Keyboard,
        Mouse
    };

    struct InputEvent {
        InputDeviceType deviceType;
        InputKeyState state;
        InputKey key;
        Vec2f position;
    };

    class IInputListener {
    public:
        virtual void handleInput( const InputEvent& event ) = 0;
    };

    class InputManager {

    public:

        InputManager();

        void processInput( const SDL_Event& event );

        /// Set an input listener that receives our output events.
        /// \param listener
        void setListener(IInputListener * const listener);

        InputEvent getLastMousePosition();

    private:

        IInputListener *m_listener;

        std::set<InputKey> m_pressedKeys;
        std::map<int,InputKey> m_sdlToInputManagerKeyMappings;
        InputEvent m_lastMousePosition;


        /// Maps a mouse button index from SDL to an InputKey enum
        /// \param index Mouse button index (1..n)
        /// \return InputKey enum
        InputKey MouseButtonFromIndex(int index);
    };

}


#endif //SDLTEST_INPUTMANAGER_H
