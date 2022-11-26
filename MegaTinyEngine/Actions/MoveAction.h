//
// Created by Peter Bone on 05/07/2020.
//

#ifndef MOVEACTION_H
#define MOVEACTION_H

#include <memory>

#include "Action.h"

namespace Engine {

    class MoveAction : public ActionInterval
    {
        public:

        MoveAction() = delete;

        explicit MoveAction( const std::shared_ptr<GameObject>& target );

        /// Create an action that moves a Sprite
        /// \param target The Sprite to move
        /// \param srcPoint The local position to start moving the Sprite from
        /// \param dstPoint The local position to move the Sprite to
        static std::shared_ptr<MoveAction> create( const std::shared_ptr<GameObject>& target, float duration, const Vec2i& srcPoint, const Vec2i& dstPoint ){
            auto action = std::make_shared<MoveAction>(target);
            action->m_duration = duration;
            action->m_srcPoint = srcPoint;
            action->m_dstPoint = dstPoint;
            action->m_target = target;

            return action;
        }

        void progress(float progress) override
        {
            int x = m_srcPoint.x + (float)(m_dstPoint.x - m_srcPoint.x) * m_progress;
            int y = m_srcPoint.y + (float)(m_dstPoint.y - m_srcPoint.y) * m_progress;
            m_target->setLocalPosition(x,y);
        }

    private:



        std::shared_ptr<GameObject> m_target;
        Vec2i m_srcPoint;
        Vec2i m_dstPoint;

    };

}


#endif //MOVEACTION_H
