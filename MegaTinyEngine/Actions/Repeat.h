//
// Created by sbeam on 11/26/22.
//

#ifndef MTENGINE_REPEAT_H
#define MTENGINE_REPEAT_H
#include "Action.h"
#include "Sprite.h"
#include <memory>

namespace Engine::Actions {

/**
 * Action that repeats another action X number of times.
 */
class Repeat : public ActionInterval
{

  public:
    Repeat( const std::shared_ptr<AbstractAction>& action_to_repeat , int repetitions ) : ActionInterval(nullptr)
    {
        m_action_to_repeat = action_to_repeat;
        m_repetitions = repetitions;
    };

    /**
     * Create an action that repeats another action.
     * @param action_to_repeat Which action to repeat.
     * @param repetitions The number of repetitions.
     * @return
     */
    static std::shared_ptr<Repeat> create( const std::shared_ptr<AbstractAction>& action_to_repeat, int repetitions )
    {
        return std::make_shared<Repeat>(action_to_repeat,repetitions);
    }

    /**
     * Create an action that repeats another action indefinitely.
     * @param action_to_repeat Which action to repeat.
     * @return
     */
    static std::shared_ptr<Repeat> createRepeatForever( const std::shared_ptr<AbstractAction>& action_to_repeat )
    {
        // Setting repetitions to -1 is actually just making the repetition counter wrap all the way around and
        // keep repeating until it reaches 0. Which will be after 2^64 iterations, which should be enough.
        // This way we save doing another compare operation and storage space for a variable indicating whether
        // to repeat indefinitely or not.
        return std::make_shared<Repeat>(action_to_repeat,-1);
    }

    void update(float dt) override;
    void progress(float progress) override;
    void reset() override;

  private:

    // The number of times to repeat the given action
    int m_repetitions;

    std::shared_ptr<AbstractAction> m_action_to_repeat;


};

}

#endif // MTENGINE_REPEAT_H
