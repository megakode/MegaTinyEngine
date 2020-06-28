//
// Created by Peter Bone on 28/06/2020.
//

#ifndef SIMPLEWESTERNGAME_IGAME_H
#define SIMPLEWESTERNGAME_IGAME_H

#include "SDL.h"
#include "InputManager.h"

namespace Engine {

    class IGame {

        virtual void initialize() = 0;
        virtual void update( float deltaTime ) = 0;
        virtual void draw( SDL_Renderer *renderer ) = 0;
        virtual void handleInput( const InputEvent& event ) = 0;

    };

}

#endif //SIMPLEWESTERNGAME_IGAME_H
