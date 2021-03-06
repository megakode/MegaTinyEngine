//
// Created by Peter Bone on 05/07/2020.
//

#ifndef SDLTEST_FADEACTION_H
#define SDLTEST_FADEACTION_H

#include <memory>
#include "../Sprite.h"
#include "Action.h"

namespace Engine {

///
/// Fade a Sprites alpha value
///

    class FadeAction : public ActionInterval
    {

    public:

        /// Create an action that fades the alpha of a Sprite from the current alpha value to 'dstAlpha'
        /// \param target Sprite to fade
        /// \param dstAlpha Destination alpha value of the fade.
        /// \return newly created FadeAction
        static std::shared_ptr<FadeAction> create( const std::shared_ptr<Sprite>& target, float duration, float srcAlpha, float dstAlpha )
        {
            auto fadeAction = std::make_shared<FadeAction>();
            fadeAction->m_sprite = target;
            fadeAction->m_startAlpha = srcAlpha;
            fadeAction->m_stopAlpha = dstAlpha;
            fadeAction->m_duration = duration;
            return fadeAction;
        }

        void progress(float progress)
        {
            float currentAlpha = m_startAlpha + (m_stopAlpha-m_startAlpha) * progress;
            m_sprite->setAlpha(currentAlpha);
        }

    private:

        // The starting value of the alpha fade
        float m_startAlpha;
        // The end value of the alpha fade
        float m_stopAlpha;

        std::shared_ptr<Sprite> m_sprite;

    };

}


#endif //SDLTEST_FADEACTION_H
