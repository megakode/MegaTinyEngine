//
// Created by Peter Bone on 04/06/2020.
//

#ifndef ANIMATION_H
#define ANIMATION_H

#include "SpriteFrame.h"
#include <cassert>
#include <string>
#include <vector>

namespace Engine
{

enum class AnimationType
{
    Manual,
    PlayOnce,
    PlayOnceAndDestroy, // Removes the Sprite from parent after animation is finished
    Loop,
    PingPong
};

enum class AnimationDirection
{
    Forward,
    Reverse
};

struct SpriteAnimation
{

    AnimationType type = AnimationType::PingPong;
    AnimationDirection direction = AnimationDirection::Forward;

    int numberOfFrames = 1;
    int currentFrame = 0;

    int ticksPrFrame = 300;
    int ticksSinceLastUpdate = 0;

    bool isFinished = false;

    std::string textureId;

    std::vector<SpriteFrame> frames;

    SpriteFrame *getCurrentFrame()
    {
        assert(currentFrame < frames.size());
        return &frames[currentFrame];
    }

    void generateFrames(int numberOfFrames, int startx, int starty, int width, int height)
    {
        this->numberOfFrames = numberOfFrames;
        for (int i = 0; i < numberOfFrames; i++)
        {
            frames.emplace_back(startx + width * i, starty, width, height);
        }
    }
};

} // namespace Engine

#endif // ANIMATION_H
