//
// Created by Peter Bone on 15/06/2020.
//

#include "InputManager.h"

namespace Engine {

    InputManager::InputManager() {

        m_listener = nullptr;

        m_sdlToInputManagerKeyMappings[SDLK_LEFT] = InputKey::Left;
        m_sdlToInputManagerKeyMappings[SDLK_RIGHT] = InputKey::Right;
        m_sdlToInputManagerKeyMappings[SDLK_UP] = InputKey::Up;
        m_sdlToInputManagerKeyMappings[SDLK_DOWN] = InputKey::Down;
        m_sdlToInputManagerKeyMappings[SDLK_SPACE] = InputKey::Space;

        m_sdlToInputManagerKeyMappings[SDLK_a] = InputKey::A;
        m_sdlToInputManagerKeyMappings[SDLK_s] = InputKey::S;
        m_sdlToInputManagerKeyMappings[SDLK_d] = InputKey::D;
        m_sdlToInputManagerKeyMappings[SDLK_f] = InputKey::F;

    }

    void InputManager::processInput(const SDL_Event &event) {

        InputEvent inputEvent{};

        // Determine if we pressed or released a key

        if( event.type == SDL_KEYDOWN ){
            inputEvent.state = InputKeyState::Pressed;
        } else if( event.type == SDL_KEYUP ){
            inputEvent.state = InputKeyState::Released;
        } else {
            // Unsupported type
            return;
        }

        // Map the key from SDL to InputManager

        if( m_sdlToInputManagerKeyMappings.count(event.key.keysym.sym) ){
            inputEvent.key = m_sdlToInputManagerKeyMappings[event.key.keysym.sym];
        } else {
            // No SDL -> InputManager key mapping defined
            return;
        }

        // Filter key-repeat
        if( inputEvent.state == InputKeyState::Pressed && m_pressedKeys.count(inputEvent.key) ){
            // Key was already pressed
            return;
        }

        if( inputEvent.state == InputKeyState::Pressed ){
            m_pressedKeys.insert(inputEvent.key);
        } else {
            m_pressedKeys.erase(inputEvent.key);
        }


        // Send the event to our listener

        if( m_listener != nullptr )
        {
            m_listener->handleInput(inputEvent);
        }

    }

    void InputManager::setListener(IInputListener * const listener)
    {
        m_listener = listener;
    }

}