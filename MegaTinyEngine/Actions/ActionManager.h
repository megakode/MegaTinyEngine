//
// Created by Peter Bone on 04/07/2020.
//

#ifndef SDLTEST_ACTIONMANAGER_H
#define SDLTEST_ACTIONMANAGER_H


#include <memory>
#include "Action.h"

namespace Engine {

    class ActionManager
    {

    public:

        void addAction( const std::shared_ptr<Action>& action );

        void update( float dt );

    private:

        std::vector<std::shared_ptr<Action>> m_actions;
    };

}


#endif //SDLTEST_ACTIONMANAGER_H
