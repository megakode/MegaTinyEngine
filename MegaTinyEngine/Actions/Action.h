//
// Created by Peter Bone on 04/07/2020.
//

#ifndef ACTION_H
#define ACTION_H

#include "../Base.h"
#include "MegaTinyEngine/GameObjects/Sprite.h"

namespace Engine
{
    class Action {
    public:

        Action() = delete;

        explicit Action( const std::shared_ptr<GameObject>& gameObject );

        virtual void update(float dt);

        bool isDone() const;

        /// Set the current action to done, without progressing it to its finishing stage.
        void stop();

         /// Reset the progress and state of an Action
        virtual void reset() = 0;

        /// The + operator can chain actions sequentially, and return one action that runs the two added ones.
        friend std::shared_ptr<Action> operator+(std::shared_ptr<Action> firstAction, const std::shared_ptr<Action>& otherAction);

        std::shared_ptr<GameObject> gameObject;

    protected:
        std::shared_ptr<Action> nextAction = nullptr;

        bool m_isDone = false;
    };

    class ActionInterval : public Action, std::enable_shared_from_this<ActionInterval>
    {
    public:

        explicit ActionInterval( const std::shared_ptr<GameObject>& target ) : Action(target){};

        void update( float dt) override;
        void reset() override;
        virtual void progress(float progress) = 0;

        /// How long the duration of this Action is supposed to be
        float m_duration = 0;

        /// How much time has elapsed since the Action started
        float m_elapsed = 0;

    protected:

        /// Float that indicates the Actions progress (0.0 -> 1.0).
        /// Subclasses should look at this value when determining the state of its animations.
        float m_progress = 0;

    };

    class ActionInstant : public Action {

    public:

        explicit ActionInstant( const std::shared_ptr<GameObject>& target ) : Action(target){};

        virtual void execute() = 0;

        void update(float dt) override;

        void reset() override;

        bool m_hasExecuted = false;

    };


}


#endif //ACTION_H
