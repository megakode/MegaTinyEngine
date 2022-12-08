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

enum class EasingType {
    None,
    OutExpo,
    InExpo,
    InOutExpo,
};

class Easing {

private:

    static constexpr float PI = 3.1415926545f;

    inline static float easeOutExpo(float x) { return std::min(1.0f, 1.0f - std::pow(2.0f, -10.0f * x)); }

    inline static float easeInExpo(float x) { return std::max(0.f, std::pow(2.0f, 10.0f * x - 10.0f)); }

    inline static float easeInOutExpo(float x) { return std::max(0.0f, std::min(1.0f, x < 0.5f ? std::pow(2.0f, 20.0f * x - 10) / 2.0f : (2 - std::pow(2.0f, -20.0f * x + 10.0f)) / 2.0f)); }

    inline static float easeInBack(float t) { return t * t * (2.70158f * t - 1.70158f); }

    inline static float easeOutBack(float t) { return 1 + (--t) * t * (2.70158f * t + 1.70158f); }

    inline static float easeInOutBack(float t)
    {
        if (t < 0.5) {
            return t * t * (7 * t - 2.5F) * 2;
        } else {
            t--;
            return 1 + (t) * t * 2 * (7 * t + 2.5F);
        }
    }

    float easeInElastic(float t)
    {
        const float t2 = t * t;
        return t2 * t2 * sinf(t * PI * 4.5);
    }

    float easeOutElastic(float t)
    {
        const float t2 = (t - 1) * (t - 1);
        return 1 - t2 * t2 * cosf(t * PI * 4.5f);
    }

    float easeInOutElastic(float t)
    {
        float t2;
        if (t < 0.45) {
            t2 = t * t;
            return 8 * t2 * t2 * sinf(t * PI * 9.0f);
        } else if (t < 0.55) {
            return 0.5f + 0.75f * sinf(t * PI * 4);
        } else {
            t2 = (t - 1) * (t - 1);
            return 1 - 8 * t2 * t2 * sinf(t * PI * 9);
        }
    }

    float easeInBounce(float t) { return powf(2, 6 * (t - 1)) * abs(sinf(t * PI * 3.5f)); }

    float easeOutBounce(float t) { return 1 - powf(2, -6 * t) * abs(cosf(t * PI * 3.5f)); }

    float easeInOutBounce(float t)
    {
        if (t < 0.5) {
            return 8 * powf(2, 8.0f * (t - 1)) * abs(sinf(t * PI * 7));
        } else {
            return 1 - 8 * powf(2, -8.0f * t) * abs(sinf(t * PI * 7));
        }
    }

    static inline std::map<EasingType, const std::function<float(float)>> easingDispatchTable {
        { EasingType::None, [](float x) { return x; }  },
        { EasingType::OutExpo, [](float x) { return easeOutExpo(x); }  },
        { EasingType::InExpo, [](float x) { return easeInExpo(x); } },
        { EasingType::InOutExpo, [](float x) { return easeInOutExpo(x); } },
    };

public:

    static float value(EasingType easingType, float x) {
        return easingDispatchTable[easingType](x);
    }
};

}

#endif // EASINGS_H
