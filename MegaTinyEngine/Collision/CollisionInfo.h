//
// Created by peter on 08/07/2020.
//

#ifndef COLLISIONINFO_H
#define COLLISIONINFO_H

#include "BoxCollider.h"
#include "GameObject.h"
#include <memory>

namespace Engine {

    struct CollisionInfo {

        std::shared_ptr<BoxCollider> first;
        std::shared_ptr<BoxCollider> second;

    };

}

#endif // COLLISIONINFO_H
