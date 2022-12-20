//
// Created by Peter Bone on 04/07/2020.
//

#include <iostream>
#include "ActionManager.h"

namespace Engine {

void ActionManager::addAction(const std::shared_ptr<AbstractAction>& action)
{
    m_actions.push_back(action);
}

void ActionManager::update(float dt)
{
    erase_if(m_actions, [&](auto action){
        action->update(dt);
        return action->isDone();
    });
}


}
