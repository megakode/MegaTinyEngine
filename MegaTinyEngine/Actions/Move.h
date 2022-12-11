//
// Created by Peter Bone on 05/07/2020.
//

#ifndef MOVEACTION_H
#define MOVEACTION_H

#include <memory>

#include "Action.h"

namespace Engine::Actions {

    class Move : public ActionInterval
    {
        public:

        Move() = delete;

        explicit Move( const std::shared_ptr<GameObject>& target ) : ActionInterval(target) { };

        /// Create an action that moves a Sprite
        /// \param target The Sprite to move
        /// \param fromPoint The local position to start moving the Sprite from
        /// \param toPoint The local position to move the Sprite to
        static std::shared_ptr<Move> create( const std::shared_ptr<GameObject>& target, float duration, const Vec2i& fromPoint, const Vec2i& toPoint, EasingType easingType = EasingType::None);

        void progress(float progress) override
        {
            int x = m_fromPoint.x + (float)(m_toPoint.x - m_fromPoint.x) * progress;
            int y = m_fromPoint.y + (float)(m_toPoint.y - m_fromPoint.y) * progress;
            m_target->setLocalPosition(x,y);
        }

        /**
         * The point that the Action moves the target GameObject from.
         */
        Vec2i& FromPoint(){
            return m_fromPoint;
        }

        /**
         * The point that the Action moves the target GameObject towards.
         */
        Vec2i& ToPoint(){
            return m_toPoint;
        }

    private:

        std::shared_ptr<GameObject> m_target;
        Vec2i m_fromPoint;
        Vec2i m_toPoint;

    };

}

#endif //MOVEACTION_H
