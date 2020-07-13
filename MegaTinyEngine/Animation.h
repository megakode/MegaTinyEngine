//
// Created by Peter Bone on 04/06/2020.
//

#ifndef SDLTEST_ANIMATION_H
#define SDLTEST_ANIMATION_H

#include <vector>
#include "SpriteFrame.h"

namespace Engine{

enum class AnimationType {
    PlayOnce,
    Loop,
    PingPong,
    Manual
};

enum class AnimationDirection {
    Forward,
    Reverse
};

struct Animation {

    AnimationType type = AnimationType::PingPong;
    AnimationDirection direction = AnimationDirection::Forward;

    int numberOfFrames = 1;
    int currentFrame = 0;

    int ticksPrFrame = 300;
    int ticksSinceLastUpdate = 0;

    bool isFinished = false;
};

struct SpriteAnimation : Animation {

    std::vector<SpriteFrame> frames;

    SpriteFrame* getCurrentFrame(){
        return &frames[currentFrame];
    }

    void generateFrames(int numberOfFrames, int startx, int starty, int width, int height ){
        this->numberOfFrames = numberOfFrames;
        for(int i = 0 ; i < numberOfFrames ; i++ ){
            frames.emplace_back(startx+width*i,starty,width,height);
        }
    }
};

}

#endif //SDLTEST_ANIMATION_H
