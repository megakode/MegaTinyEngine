//
// Created by Peter Bone on 18/06/2020.
//

#ifndef SDLTEST_RECT_H
#define SDLTEST_RECT_H

namespace Engine {

    struct Rect {
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;

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

        bool isZeroSize(){
            return width == 0 && height == 0;
        }
    };


}


#endif //SDLTEST_RECT_H
