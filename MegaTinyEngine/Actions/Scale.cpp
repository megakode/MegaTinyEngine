//
// Created by Peter Bone on 11/12/2022.
//

#include "Scale.h"

namespace Engine::Actions
{

std::shared_ptr<Scale> Scale::create(const std::shared_ptr<Sprite>& target, float duration, const Vec2f& fromScale, const Vec2f& toScale, EasingType easingType)
{
    auto action = std::make_shared<Scale>(target,duration);
    action->fromScale = fromScale;
    action->toScale = toScale;
    action->target = target;
    action->m_duration = duration;

    return action;
}

void Scale::progress(float progress)
{
    Vec2f scale;
    scale.x = fromScale.x + (float)(toScale.x - fromScale.x) * progress;
    scale.y = fromScale.y + (float)(toScale.y - fromScale.y) * progress;
    target->setScaling(scale);
}

}