//
// Created by Peter Bone on 15/06/2020.
//

#include <iostream>
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

    InputKey InputManager::MouseButtonFromIndex( int index ){
        switch(index){
            case 1:
                return InputKey::MouseButtonLeft;
            case 3:
                return InputKey::MouseButtonRight;
            default:
                return InputKey::UNKNOWN;
        }
    };

    void InputManager::processInput(const SDL_Event &event) {

        InputEvent inputEvent{};

        // Determine if we pressed or released a key

        if( event.type == SDL_KEYDOWN ){
            inputEvent.deviceType = InputDeviceType::Keyboard;
            inputEvent.state = InputKeyState::Pressed;
        } else if( event.type == SDL_KEYUP ){
            inputEvent.deviceType = InputDeviceType::Keyboard;
            inputEvent.state = InputKeyState::Released;
        } else if( event.type == SDL_MOUSEBUTTONDOWN ){
            inputEvent.deviceType = InputDeviceType::Mouse;
            inputEvent.state = InputKeyState::Pressed;
            inputEvent.key = MouseButtonFromIndex(event.button.button);
        } else if( event.type == SDL_MOUSEBUTTONUP ){
            inputEvent.deviceType = InputDeviceType::Mouse;
            inputEvent.state = InputKeyState::Released;
            inputEvent.key = MouseButtonFromIndex(event.button.button);
        } else if( event.type == SDL_MOUSEMOTION ) {
            inputEvent.deviceType = InputDeviceType::Mouse;
            inputEvent.state = InputKeyState::Moved;
        } else {
            // Unsupported type
            return;
        }



        if( inputEvent.deviceType == InputDeviceType::Keyboard ){

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
        } else if (inputEvent.deviceType == InputDeviceType::Mouse){

            inputEvent.position.x = event.motion.x;
            inputEvent.position.y = event.motion.y;

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