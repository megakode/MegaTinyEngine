//
// Created by Peter Bone on 04/07/2020.
//

#include <iostream>
#include "ActionManager.h"

namespace Engine {

void ActionManager::addAction(const std::shared_ptr<Action>& action)
{
    m_actions.push_back(action);
}

void ActionManager::update(float dt)
{

    auto iterator = m_actions.begin();

    while( iterator != m_actions.end() ){

        iterator->get()->update(dt);
        if(iterator->get()->isDone()){
            iterator = m_actions.erase(iterator);
        } else {
            iterator++;
        }


    }


}


}
