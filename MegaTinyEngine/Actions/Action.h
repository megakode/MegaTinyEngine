//
// Created by Peter Bone on 04/07/2020.
//

#ifndef SDLTEST_ACTION_H
#define SDLTEST_ACTION_H

#include "../Base.h"
#include "../Sprite.h"

namespace Engine
{
    class Action {
    public:

        virtual void update(float dt);

        bool isDone() const;

        /// Set the current action to done, without progressing it to its finishing stage.
        void stop();

        /// The + operator can chain actions sequentially, and return one action that runs the two added ones.
        friend std::shared_ptr<Action> operator+(std::shared_ptr<Action> firstAction, const std::shared_ptr<Action>& otherAction);

    protected:

        std::shared_ptr<Action> nextAction = nullptr;

        bool m_isDone = false;

    };

    class ActionInterval : public Action, std::enable_shared_from_this<ActionInterval>
    {
    public:
        void update( float dt) override;
        virtual void progress(float progress) = 0;

    protected:

        /// Float that indicates the Actions progress (0.0 -> 1.0).
        /// Subclasses should look at this value when determining the state of its animations.
        float m_progress = 0;

        /// How long the duration of this Action is supposed to be
        float m_duration = 0;

        /// How much time has elapsed since the Action started
        float m_elapsed = 0;

    };

    class ActionInstant : public Action {

    public:

        virtual void execute() = 0;

        void update(float dt) override;

        bool m_hasExecuted = false;

    };


}


#endif //SDLTEST_ACTION_H
