//
// Created by Peter Bone on 05/07/2020.
//

#ifndef FADEACTION_H
#define FADEACTION_H

#include "Action.h"
#include "Sprite.h"
#include <memory>

namespace Engine::Actions {

///
/// Fade a Sprites alpha value
///

    class Fade : public ActionInterval
    {

    public:
      Fade( const std::shared_ptr<Sprite>& target ) : ActionInterval(target)
        {

        };

        /// Create an action that fades the alpha of a Sprite from the current alpha value to 'dstAlpha'
        /// \param target Sprite to fade
        /// \param dstAlpha Destination alpha value of the fade.
        /// \return newly created Fade
        static std::shared_ptr<Fade> create( const std::shared_ptr<Sprite>& target, float duration, float srcAlpha, float dstAlpha )
        {
            auto fadeAction = std::make_shared<Fade>(target);
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


#endif //FADEACTION_H
