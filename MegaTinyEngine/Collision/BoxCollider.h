//
// Created by Peter Bone on 19/06/2020.
//

#ifndef SDLTEST_BOXCOLLIDER_H
#define SDLTEST_BOXCOLLIDER_H


#include <cstdint>
#include "../Rect.h"

namespace Engine {

    class BoxCollider {

    public:
        virtual Rect bbox() = 0;

        /// The collision mask bits are AND'ed together when the collision manager determines if two objects collide. If the results is > 0, a collision occurs.
        std::uint32_t collision_mask_bits = 0;
        std::uint32_t collision_group_id = 0;
    };


}


#endif //SDLTEST_BOXCOLLIDER_H
