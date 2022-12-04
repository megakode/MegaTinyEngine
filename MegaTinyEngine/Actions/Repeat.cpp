//
// Created by sbeam on 11/26/22.
//
#include "Repeat.h"

namespace Engine::Actions {

void Repeat::update(float dt)
{
    if( !m_isDone ) {

        m_elapsed += dt;

        if(m_action_to_repeat->isDone()){

            if(m_repetitions == 1){
                m_isDone = true;
            } else {
                m_repetitions--;
                m_action_to_repeat->reset();
            }
        }
        else
        {
            m_action_to_repeat->update(dt);
        }



    }

//    ActionInterval::update(dt);
}

void Repeat::reset()
{
    m_action_to_repeat->reset();
    m_repetitions = 0;
    ActionInterval::reset();
}

void Repeat::progress(float progress)
{
}

}