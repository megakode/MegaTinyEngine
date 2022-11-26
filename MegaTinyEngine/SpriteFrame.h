//
// Created by Peter Bone on 04/06/2020.
//

#ifndef SPRITEFRAME_H
#define SPRITEFRAME_H

namespace Engine {

    struct SpriteFrame {
        SpriteFrame(){};
        SpriteFrame(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {};
        int x;
        int y;
        int w;
        int h;
    };

}


#endif //SPRITEFRAME_H
