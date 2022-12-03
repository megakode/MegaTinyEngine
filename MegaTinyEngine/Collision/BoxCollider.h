//
// Created by Peter Bone on 19/06/2020.
//

#ifndef _BOXCOLLIDER_H
#define _BOXCOLLIDER_H

#include "Base.h"
#include <cstdint>

namespace Engine {

    class BoxCollider {

    public:
        virtual Rect bbox() = 0;

        /// The collision mask bits are AND'ed together when the collision manager determines if two objects collide. If the results is > 0, a collision occurs.
        std::uint32_t collision_mask_bits = 0;
        std::uint32_t collision_group_id = 0;
    };


}


#endif //BOXCOLLIDER_H
