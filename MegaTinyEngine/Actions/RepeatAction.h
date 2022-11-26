//
// Created by sbeam on 11/26/22.
//

#ifndef MTENGINE_REPEATACTION_H
#define MTENGINE_REPEATACTION_H
#include "Action.h"
#include "MegaTinyEngine/GameObjects/Sprite.h"
#include <memory>

namespace Engine {

///
/// Repeat another Action.
///

class RepeatAction : public ActionInterval
{

  public:

    RepeatAction( const std::shared_ptr<Action>& action_to_repeat , int repetitions ) : ActionInterval(action_to_repeat->gameObject)
    {
        m_action_to_repeat = action_to_repeat;
        m_repetitions = repetitions;
    };

    /// Create an action that fades the alpha of a Sprite from the current alpha value to 'dstAlpha'
    /// \param target Sprite to fade
    /// \param dstAlpha Destination alpha value of the fade.
    /// \return newly created FadeAction
    static std::shared_ptr<RepeatAction> create( const std::shared_ptr<Action>& action_to_repeat, int repetitions )
    {
        auto action = std::make_shared<RepeatAction>(action_to_repeat,repetitions);

        return action;
    }

    void update(float dt) override;

    void progress(float progress) override;

  private:

    // The number of times to repeat the given action
    int m_repetitions;

    std::shared_ptr<Action> m_action_to_repeat;


};

}

#endif // MTENGINE_REPEATACTION_H
