//
// Created by peter on 08/07/2020.
//

#ifndef SIMPLESHARKGAME_COLLISIONINFO_H
#define SIMPLESHARKGAME_COLLISIONINFO_H


#include <memory>
#include <MegaTinyEngine/GameObject.h>
#include "BoxCollider.h"

namespace Engine {

    struct CollisionInfo {



        std::shared_ptr<BoxCollider> first;
        std::shared_ptr<BoxCollider> second;

    };

}

#endif //SIMPLESHARKGAME_COLLISIONINFO_H
