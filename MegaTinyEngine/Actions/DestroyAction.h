//
// Created by Peter Bone on 05/07/2020.
//

#ifndef DESTROYACTION_H
#define DESTROYACTION_H
#include <memory>
#include "Action.h"
#include "Sprite.h"

namespace Engine
{
    class DestroyAction : public ActionInstant
    {
    public:

        explicit DestroyAction( const std::shared_ptr<Sprite>& target ) : ActionInstant(target) {};

        static std::shared_ptr<DestroyAction> create( const std::shared_ptr<Sprite>& target ){
            return std::make_shared<DestroyAction>(target);
        }

        void execute() override
        {
            if(gameObject!=nullptr){
                gameObject->removeFromParent();
            }
        }

    };
}


#endif //DESTROYACTION_H
