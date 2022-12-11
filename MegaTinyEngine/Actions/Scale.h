//
// Created by Peter Bone on 11/12/2022.
//

#ifndef MTENGINE_SCALE_H
#define MTENGINE_SCALE_H

#include "Action.h"
#include "Sprite.h"

namespace Engine::Actions
{

class Scale  : public ActionInterval {

public:

    Scale() = delete;

    /**
     * Don't call this directly! Use the create() method.
     */
    explicit Scale( const std::shared_ptr<Sprite>& target , float duration) : ActionInterval(target, duration) { };

    /// Create an action that scales a Sprite.
    /// \param target The Sprite to scale.
    /// \param fromScale The scale value to start from.
    /// \param toScale The scale value to end at.
    static std::shared_ptr<Scale> create(const SpritePtr& target, float duration, const Vec2f& fromScale, const Vec2f& toScale, EasingType easingType = EasingType::None);

    void progress(float progress) override;

    Vec2f fromScale {1.0f, 1.0f};
    Vec2f toScale {1.0f, 1.0f};
    SpritePtr target;

};

}


#endif // MTENGINE_SCALE_H
