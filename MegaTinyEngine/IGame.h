//
// Created by Peter Bone on 28/06/2020.
//

#ifndef IGAME_H
#define IGAME_H

#include "SDL.h"
#include "InputManager.h"

namespace Engine {

    class IGame : public IInputListener {

    public:

        virtual void initialize() = 0;
        virtual void update( float deltaTime ) = 0;
        virtual void draw( SDL_Renderer *renderer ) = 0;
        void handleInput( const InputEvent& event ) override = 0;

    };

}

#endif //IGAME_H
