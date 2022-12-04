//
// Created by Peter Bone on 05/07/2020.
//

#ifndef DESTROYACTION_H
#define DESTROYACTION_H
#include <memory>
#include "Action.h"
#include "Sprite.h"

namespace Engine::Actions
{
    /**
     * Action that destroys a GameObject by removing it from its parent.
     * Note that there is no guarantee that the GameObject will then be deallocated,
     * as there can be other shared_ptrs holding a reference to it.
     */
    class Destroy : public ActionInstant
    {
      public:
        explicit Destroy(const std::shared_ptr<Sprite> &target) : ActionInstant(target){};

        static std::shared_ptr<Destroy> create(const std::shared_ptr<Sprite> &target)
        {
            return std::make_shared<Destroy>(target);
        }

        void execute() override
        {
            if (gameObject != nullptr)
            {
                gameObject->removeFromParent();
            }
        }
    };
}

#endif //DESTROYACTION_H
