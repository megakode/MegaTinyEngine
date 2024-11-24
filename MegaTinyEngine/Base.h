//
// Created by Peter Bone on 07/08/2020.
//

#pragma once

#include <cmath>
#include <stdint.h>

namespace Engine {

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

    struct Rect {
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;

        bool intersects( const Vec2i& point ) const {
            return ( point.x >= x && point.x <= x + width && point.y >= y && point.y <= y + height);
        }

        bool intersectsLine(const Vec2i& p1, const Vec2i& p2) {
    
            struct AABB {
                Vec2i min;
                Vec2i max;
            };

            AABB box = { {this->x, this->y}, {this->x+this->width, this->y+this->height} };

            // Check if either endpoint of the line is inside the AABB
            if (intersects(p1) || intersects(p2)) {
                return true;
            }

            // Get the intersection points for the line and the box edges
            float tMin = 0.0f, tMax = 1.0f;
            Vec2i d = {p2.x - p1.x, p2.y - p1.y}; // Line direction

            // Lambda to test intersection with a slab
            auto testSlab = [&](float p, float d, float min, float max) -> bool {
                if (d != 0.0f) {
                    float t0 = (min - p) / d;
                    float t1 = (max - p) / d;
                    if (t0 > t1) std::swap(t0, t1);
                    tMin = std::max(tMin, t0);
                    tMax = std::min(tMax, t1);
                    if (tMin > tMax) return false;
                } else if (p < min || p > max) {
                    return false;
                }
                return true;
            };

            // Test each slab (X and Y axes)
            if (!testSlab(p1.x, d.x, box.min.x, box.max.x)) return false;
            if (!testSlab(p1.y, d.y, box.min.y, box.max.y)) return false;

            return true;
        }

        bool intersects( const Rect& other ) const {
            int max_x = x+width;
            int max_y = y+height;
            int other_max_x = other.x+other.width;
            int other_max_y = other.y+other.height;

            // Other is left of us
            if( other_max_x < x ){
                return false;
            }
            // Other is right of us
            if( other.x > max_x ){
                return false;
            }

            // Other is below us
            if( other.y > max_y ){
                return false;
            }

            // Other is above us
            if( other_max_y < y){
                return false;
            }

            return true;
        }

        

        bool isZeroSize() const {
            return width == 0 && height == 0;
        }
    };




    //#define ENABLE_ASSERTS

    #define ENGINE_ASSERT(x, msg) { if(!(x)) { assert(msg,0); } }


    struct DeltaTime {
    public:

        operator float() const { return m_time; }

    private:
        float m_time;
    };

    struct ColorRGBA8 {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

}
