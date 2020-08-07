//
// Created by Peter Bone on 07/08/2020.
//

#include "Base.h"

namespace Engine {

    Vec2f::operator Vec2i() const {
        return {static_cast<int>(x), static_cast<int>(y)};
    }

    Vec2i::operator Vec2f() const {
        return {static_cast<float>(x), static_cast<float>(y)};
    }

}