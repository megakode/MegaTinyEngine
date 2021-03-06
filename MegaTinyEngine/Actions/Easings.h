//
// Created by Peter Bone on 05/07/2020.
//

#ifndef SDLTEST_EASINGS_H
#define SDLTEST_EASINGS_H

#include <cmath>
#include <algorithm>

#ifndef PI
#define PI 3.1415926545f
#endif

float easeOutExpo(float x) {
    return std::min(1.0, 1.0 - std::powf(2, -10 * x) );
}

float easeInExpo(float x){
    return std::max( 0.f , std::powf(2, 10 * x - 10) );
}

float easeInOutExpo(float x){
    return std::max(0.0f, std::min(1.0f, x < 0.5f ? std::powf(2, 20 * x - 10) / 2.0f : (2 - std::powf(2, -20 * x + 10)) / 2.0f ));
}

float easeInBack( float t ) {
    return t * t * (2.70158f * t - 1.70158f);
}

float easeOutBack( float t ) {
    return 1 + (--t) * t * (2.70158f * t + 1.70158f);
}

double easeInOutBack( float t ) {
    if( t < 0.5 ) {
        return t * t * (7 * t - 2.5f) * 2;
    } else {
        return 1 + (--t) * t * 2 * (7 * t + 2.5f);
    }
}

float easeInElastic( float t ) {
    float t2 = t * t;
    return t2 * t2 * sinf( t * PI * 4.5 );
}

float easeOutElastic( float t ) {
    float t2 = (t - 1) * (t - 1);
    return 1 - t2 * t2 * cosf( t * PI * 4.5f );
}

float easeInOutElastic( float t ) {
    float t2;
    if( t < 0.45 ) {
        t2 = t * t;
        return 8 * t2 * t2 * sinf( t * PI * 9.0f );
    } else if( t < 0.55 ) {
        return 0.5f + 0.75f * sinf( t * PI * 4 );
    } else {
        t2 = (t - 1) * (t - 1);
        return 1 - 8 * t2 * t2 * sinf( t * PI * 9 );
    }
}

float easeInBounce( float t ) {
    return powf( 2, 6 * (t - 1) ) * abs( sinf( t * PI * 3.5f ) );
}

float easeOutBounce( float t ) {
    return 1 - powf( 2, -6 * t ) * abs( cosf( t * PI * 3.5f ) );
}

float easeInOutBounce( float t ) {
    if( t < 0.5 ) {
        return 8 * powf( 2, 8.0f * (t - 1) ) * abs( sinf( t * PI * 7 ) );
    } else {
        return 1 - 8 * powf( 2, -8.0f * t ) * abs( sinf( t * PI * 7 ) );
    }
}


#endif //SDLTEST_EASINGS_H
