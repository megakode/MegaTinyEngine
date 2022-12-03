//
// Created by sbeam on 12/3/22.
//

#ifndef MTENGINE_SEQUENCE_H
#define MTENGINE_SEQUENCE_H

#include "Action.h"
#include <memory>

namespace Engine {
namespace Actions {

class Sequence : public ActionInterval
{

  public:

    explicit Sequence(const std::shared_ptr<GameObject>& gameObject) : ActionInterval(gameObject)
    {
    };

    /// Create an action that fades the alpha of a Sprite from the current alpha value to 'dstAlpha'
    /// \param target Sprite to fade
    /// \param dstAlpha Destination alpha value of the fade.
    /// \return newly created FadeAction

    //auto foo(std::convertible_to<X> auto ... args) {}

    static std::shared_ptr<Sequence> create( const std::shared_ptr<GameObject>& gameObject,  const std::vector<std::shared_ptr<AbstractAction>>& action_list )
    {
        auto seq = std::make_shared<Sequence>(gameObject);

        seq->m_action_list = action_list;

        return seq;
    }

    void update(float dt) override;
    void progress(float progress) override;
    void reset() override;

  private:

    std::vector<std::shared_ptr<AbstractAction>> m_action_list;

};

}
}

#endif // MTENGINE_SEQUENCE_H
