//
// Created by Peter Bone on 04/07/2020.
//

#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include "Base.h"
#include "GameObject.h"
#include "Easings.h"

namespace Engine
{
    class AbstractAction {
    public:

        AbstractAction() = delete;
        virtual ~AbstractAction() { };

        AbstractAction(const AbstractAction& src) = delete; // Copy constructor
        AbstractAction(AbstractAction&&) = delete; // Move constructor
        AbstractAction& operator=(const AbstractAction& other) = delete; // Copy assignment operator
        AbstractAction& operator=(AbstractAction&& other) = delete; // Move assignment operator

        explicit AbstractAction( const std::shared_ptr<GameObject>& gameObject );

        virtual void update(float dt) = 0;

        bool isDone() const;

        /// Set the current action to done, without progressing it to its finishing stage.
        void stop();

         /// Reset the progress and state of an Action
        virtual void reset() = 0;

    protected:
        bool m_isDone = false;
        // TODO: maybe remove this, as typically Sprite is more usefull and only used in ActionInterval.
        std::shared_ptr<GameObject> gameObject;
    };



    class ActionInterval : public AbstractAction, std::enable_shared_from_this<ActionInterval>
    {
    public:

        explicit ActionInterval( const std::shared_ptr<GameObject>& target, float duration = 1.0f ) : AbstractAction(target), m_duration(duration){};

        void update( float dt) override;
        void reset() override;
        virtual void progress(float progress) = 0;

        /// The easing type that progress is advanced by (linear, exponential, bounce, etc.)
        Actions::EasingType easingType = Actions::EasingType::None;

    protected:

        /// How long the duration of this Action is supposed to be
        float m_duration = 0;

        /// How much time has elapsed since the Action started
        float m_elapsed = 0;

      private:

        /// Float that indicates the Actions progress (0.0 -> 1.0).
        /// Subclasses should look at this value when determining the state of its animations.
        float m_progress = 0;

    };

    class ActionInstant : public AbstractAction {

    public:

        explicit ActionInstant( const std::shared_ptr<GameObject>& target ) : AbstractAction(target){};

        virtual void execute() = 0;

        void update(float dt) override;

        void reset() override;

        bool m_hasExecuted = false;

    };


}


#endif //ACTION_H
