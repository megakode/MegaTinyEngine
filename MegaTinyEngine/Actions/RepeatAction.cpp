//
// Created by sbeam on 11/26/22.
//
#include "RepeatAction.h"

namespace Engine {

void RepeatAction::update(float dt){
    if( !m_isDone ) {

        m_elapsed += dt;

        if(m_action_to_repeat->isDone()){
            if(m_repetitions == 1){
                //m_elapsed = m_duration;
                m_isDone = true;
            } else {
                m_repetitions--;
                m_action_to_repeat->reset();
            }
        }

        m_action_to_repeat->update(dt);

    }

    Action::update(dt);
}
void RepeatAction::progress(float progress)
{
}

}