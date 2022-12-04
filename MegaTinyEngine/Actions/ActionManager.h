//
// Created by Peter Bone on 04/07/2020.
//

#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H


#include <memory>
#include "Action.h"

namespace Engine {

    class ActionManager
    {

    public:

        void addAction( const std::shared_ptr<AbstractAction>& action );

        void update( float dt );

    private:

        std::vector<std::shared_ptr<AbstractAction>> m_actions;
    };

}


#endif //ACTIONMANAGER_H
