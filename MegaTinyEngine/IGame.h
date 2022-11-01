//
// Created by Peter Bone on 28/06/2020.
//

#ifndef IGAME_H
#define IGAME_H

#include <SDL.h>
#include "InputManager.h"
#include "Scene.h"

namespace Engine {

    /**
     * The primary interface a game must implement, for the engine to be able to run it.
     * The engines main run can be illustrated with the following pseudo code:
     *
     * game->initialize()
     * while(!quit) {
     *   game->update()
     *   game->draw()
     *   while(input_events_available)
     *      game->handleInput(next_input_event)
     * }
     *
     */
    class IGame : public IInputListener {

    public:

        virtual std::shared_ptr<Scene> initialize() = 0;
        virtual void update( float deltaTime ) = 0;
        virtual void draw( SDL_Renderer *renderer ) = 0;
        void handleInput( const InputEvent& event ) override = 0;

    };

}



#endif //IGAME_H
