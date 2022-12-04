//
// Created by Peter Bone on 05/07/2020.
//

#include "Move.h"

namespace Engine {
namespace Actions
{

std::shared_ptr<Move> Move::create(const std::shared_ptr<GameObject> &target, float duration, const Vec2i &fromPoint, const Vec2i &toPoint)
{
    auto action = std::make_shared<Move>(target);
    action->m_duration = duration;
    action->m_fromPoint = fromPoint;
    action->m_toPoint = toPoint;
    action->m_target = target;

    return action;
}

}
}