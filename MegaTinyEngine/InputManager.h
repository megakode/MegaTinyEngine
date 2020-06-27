//
// Created by Peter Bone on 15/06/2020.
//

#ifndef SDLTEST_INPUTMANAGER_H
#define SDLTEST_INPUTMANAGER_H


#include <SDL_events.h>
#include <memory>
#include <map>
#include <set>

namespace Engine {

    enum class InputKeyState {
        Pressed,
        Released
    };

    enum class InputKey {
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

    struct InputEvent {
        InputKeyState state;
        InputKey key;
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

    private:

        IInputListener *m_listener;

        std::set<InputKey> m_pressedKeys;
        std::map<int,InputKey> m_sdlToInputManagerKeyMappings;
    };

}


#endif //SDLTEST_INPUTMANAGER_H
