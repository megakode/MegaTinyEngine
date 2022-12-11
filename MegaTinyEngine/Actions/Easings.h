//
// Created by Peter Bone on 05/07/2020.
//
#include <map>

#ifndef EASINGS_H
#define EASINGS_H

#include <algorithm>
#include <cmath>
#include <functional>

namespace Engine::Actions {

/**
 * For animated visual examples of easings, check out https://easings.net
 */
enum class EasingType {
    None,
    InExpo,
    OutExpo,
    InOutExpo,
    InBack,
    OutBack,
    InOutBack,
    InElastic,
    OutElastic,
    InOutElastic,
    InBounce,
    OutBounce,
    InOutBounce
};

class Easing {

private:

    static constexpr float PI = 3.1415926545f;

    static float easeOutExpo(float x);

    static float easeInExpo(float x);

    static float easeInOutExpo(float x);

    static float easeInBack(float x);

    static float easeOutBack(float x);

    static float easeInOutBack(float x);

    static float easeInElastic(float x);

    static float easeOutElastic(float x);

    static float easeInOutElastic(float x);

    static float easeInBounce(float x);

    static float easeOutBounce(float x);

    static float easeInOutBounce(float x);

    static inline std::map<EasingType, const std::function<float(float)>> easingDispatchTable {
        { EasingType::None, [](float x) { return x; }  },
        { EasingType::InExpo, [](float x) { return easeInExpo(x); } },
        { EasingType::OutExpo, [](float x) { return easeOutExpo(x); }  },
        { EasingType::InOutExpo, [](float x) { return easeInOutExpo(x); } },
        { EasingType::InBack, [](float x) { return easeInBack(x); } },
        { EasingType::OutBack, [](float x) { return easeOutBack(x); } },
        { EasingType::InOutBack, [](float x) { return easeInOutBack(x); } },
        { EasingType::InElastic, [](float x) { return easeInElastic(x); } },
        { EasingType::OutElastic, [](float x) { return easeOutElastic(x); } },
        { EasingType::InOutElastic, [](float x) { return easeInOutElastic(x); } },
        { EasingType::InBounce, [](float x) { return easeInBounce(x); } },
        { EasingType::OutBounce, [](float x) { return easeOutBounce(x); } },
        { EasingType::InOutBounce, [](float x) { return easeInOutBounce(x); } },
    };

public:

    /**
     * Perform easing curve calculation.
     * @param easingType Type of curve (exponential out, bounce, linear, etc.)
     * @param x The input value to calculate from. Must be in the range 0.0 - 1.0.
     * @return The eased value, based on the given input x and curve type.
     */
    static float value(EasingType easingType, float x) {
        return easingDispatchTable[easingType](x);
    }
};

}

#endif // EASINGS_H
