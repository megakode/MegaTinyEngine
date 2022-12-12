#include <map>
#include <cmath>
#include "Easings.h"

namespace Engine::Actions {

inline float Easing::easeOutExpo(float x){
    return std::min(1.0f, 1.0f - std::pow(2.0f, -10.0f * x));
}

inline float Easing::easeInExpo(float x){
    return std::max(0.f, std::pow(2.0f, 10.0f * x - 10.0f));
}

inline float Easing::easeInOutExpo(float x) {
    return std::max(0.0f, std::min(1.0f, x < 0.5f ? std::pow(2.0f, 20.0f * x - 10) / 2.0f : (2 - std::pow(2.0f, -20.0f * x + 10.0f)) / 2.0f));
}

inline float Easing::easeInBack(float x) {
    return x * x * (2.70158f * x - 1.70158f);
}

inline float Easing::easeOutBack(float x) {
    constexpr float c1 = 1.70158;
    constexpr float c3 = c1 + 1;

    return 1 + c3 * powf(x - 1, 3) + c1 * powf(x - 1, 2);

    // Alternative function without pow. Not tested though.
    // return 1 + (--t) * t * (2.70158f * t + 1.70158f);
}

inline float Easing::easeInOutBack(float x)
{
    if (x < 0.5) {
        return x * x * (7 * x - 2.5F) * 2;
    } else {
        x--;
        return 1 + (x) * x * 2 * (7 * x + 2.5f);
    }
}

inline float Easing::easeInElastic(float x)
{

    const float t2 = x * x;
    return t2 * t2 * sinf(x * PI * 4.5f);
}

inline float Easing::easeOutElastic(float x)
{
    const float t2 = (x - 1) * (x - 1);
    return 1 - t2 * t2 * cosf(x * PI * 4.5f);
}

inline float Easing::easeInOutElastic(float x)
{
    float t2;
    if (x < 0.45) {
        t2 = x * x;
        return 8 * t2 * t2 * sinf(x * PI * 9.0f);
    } else if (x < 0.55) {
        return 0.5f + 0.75f * sinf(x * PI * 4);
    } else {
        t2 = (x - 1) * (x - 1);
        return 1 - 8 * t2 * t2 * sinf(x * PI * 9);
    }
}

inline float Easing::easeInBounce(float x) {

    return powf(2, 6 * (x - 1)) * std::fabs(sinf(x * PI * 3.5f));
}

inline float Easing::easeOutBounce(float x) {
    return 1 - powf(2, -6 * x) * std::fabs(cosf(x * PI * 3.5f));
}

inline float Easing::easeInOutBounce(float x)
{
    if (x < 0.5) {
        return 8.0f * powf(2, 8.0f * (x - 1)) * std::fabs(sinf(x * PI * 7));
    } else {
        return 1 - 8.0f * powf(2, -8.0f * x) * std::fabs(sinf(x * PI * 7));
    }
}

}