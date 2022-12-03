//
// Created by Peter Bone on 04/07/2020.
//

#ifndef ACTION_H
#define ACTION_H

#include "GameObject.h"
#include "Base.h"

namespace Engine
{
    class AbstractAction {
    public:

        AbstractAction() = delete;
        virtual ~AbstractAction() = default;

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

        std::shared_ptr<GameObject> gameObject;

    protected:

        bool m_isDone = false;
    };

    class ActionInterval : public AbstractAction, std::enable_shared_from_this<ActionInterval>
    {
    public:

        explicit ActionInterval( const std::shared_ptr<GameObject>& target ) : AbstractAction(target){};

        void update( float dt) override;
        void reset() override;
        virtual void progress(float progress) = 0;

    protected:

        /// How long the duration of this Action is supposed to be
        float m_duration = 0;

        /// How much time has elapsed since the Action started
        float m_elapsed = 0;

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
