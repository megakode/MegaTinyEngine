//
// Created by sbeam on 12/3/22.
//

#include "Sequence.h"
void Engine::Actions::Sequence::update(float dt)
{
    bool done = true;

    for( auto &action : m_action_list )
    {
        if(!action->isDone()){
            action->update(dt);
            done = false;
            break;
        }
    }

    if(done){m_isDone = true;}
//    ActionInterval::update(dt);
}
void Engine::Actions::Sequence::progress(float progress)
{
}
void Engine::Actions::Sequence::reset()
{
    for( auto &action : m_action_list )
    {
        action->reset();
    }
    ActionInterval::reset();
}
