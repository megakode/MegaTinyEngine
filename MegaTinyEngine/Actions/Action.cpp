//
// Created by Peter Bone on 04/07/2020.
//

#include <algorithm>
#include "Action.h"
#include "Easings.h"

namespace Engine {

    void Action::update(float dt)
    {
        if( nextAction != nullptr && m_isDone ){
            nextAction->update(dt);
        }
    }

    bool Action::isDone() const
    {
        bool nextActionDone = true;

        if( nextAction != nullptr ){
            nextActionDone = nextAction->isDone();
        }
        return m_isDone && nextActionDone;
    }

    std::shared_ptr<Action> operator+(std::shared_ptr<Action> firstAction, const std::shared_ptr<Action> &otherAction)
    {
        firstAction->nextAction = otherAction;
        return firstAction;
    }

    ///
    /// Action interval
    ///

    void ActionInterval::update(float dt){
        if( !m_isDone ) {
            m_elapsed += dt;

            if(m_elapsed >= m_duration){
                m_elapsed = m_duration;
                m_isDone = true;
            }

            m_progress = easeOutExpo( std::min(m_elapsed / m_duration , 1.0f) );
            progress(m_progress);
        }

        Action::update(dt);
    }

    ///
    /// Action Instant
    ///

    void ActionInstant::update(float dt)
    {
        if(!m_hasExecuted){
            execute();
            m_isDone = true;
            m_hasExecuted = true;
        }

        Action::update(dt);
    }
}