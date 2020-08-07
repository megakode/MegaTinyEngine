//
// Created by Peter Bone on 07/08/2020.
//

#ifndef SIMPLEWESTERNGAME_BASE_H
#define SIMPLEWESTERNGAME_BASE_H

#include <cmath>

struct Vec2i;

struct Vec2f {
    float x  = 0;
    float y = 0;
    operator Vec2i() const;
};


struct Vec2i {
    int x  = 0;
    int y = 0;

    operator Vec2f() const;

    Vec2i operator - (const Vec2i& other ) const { return Vec2i{x-other.x,y-other.y};};
    Vec2i operator + (const Vec2i& other ) const { return Vec2i{x+other.x,y+other.y};};
    Vec2i operator * (const Vec2i& other ) const { return Vec2i{x*other.x,y*other.y};};

    int dist( const Vec2i& other ) const { return std::sqrt( (other.x-x)*(other.x-x) + (other.y-y)*(other.y-y) ); };
};


//#define ENABLE_ASSERTS

#define ENGINE_ASSERT(x, msg) { if(!(x)) { assert(msg,0); } }


struct DeltaTime {
public:

    operator float() const { return m_time; }

private:
    float m_time;
};


#endif //SIMPLEWESTERNGAME_BASE_H
