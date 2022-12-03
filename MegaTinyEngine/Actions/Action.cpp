//
// Created by Peter Bone on 04/07/2020.
//

#include <algorithm>
#include <memory>
#include "Action.h"

namespace Engine {

    AbstractAction::AbstractAction(const std::shared_ptr<GameObject> &gameObject) : gameObject(gameObject)
    {

    }

    bool AbstractAction::isDone() const
    {
        return m_isDone;
    }

    void AbstractAction::stop() {
        m_isDone = true;
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

//            m_progress = easeOutExpo( std::min(m_elapsed / m_duration , 1.0f) );
            m_progress = std::min(m_elapsed / m_duration , 1.0F);
            progress(m_progress);
        }

    }

    void ActionInterval::reset()
    {
        m_progress = 0;
        m_elapsed = 0;
        m_isDone = false;
    }

    ///
    /// Action Instant
    ///

    void ActionInstant::update(float  /*dt*/)
    {
        if(!m_hasExecuted){
            execute();
            m_isDone = true;
            m_hasExecuted = true;
        }

    }
    void ActionInstant::reset()
    {
        m_hasExecuted = false;
        m_isDone = false;
    }
}