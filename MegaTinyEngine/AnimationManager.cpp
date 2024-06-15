//
// Created by Peter Bone on 29/05/2020.
//

#include "AnimationManager.h"
#include <assert.h>
#include <iostream>
#include <string>

namespace Engine {

/// *******************************************************************
///
/// addAnimations
///
/// *******************************************************************

void AnimationManager::addAnimationPreset(const std::string_view& id, const SpriteAnimation& animation) { m_animationPresets[id] = animation; }

std::shared_ptr<SpriteAnimation> AnimationManager::createAnimation(const std::string_view& preset_id, bool addToList)
{

    if (m_animationPresets.count(preset_id) == 0) {
        std::cout << "Trying to create an animation from an ID which has no preset in AnimationManager";
        assert(0);
        return nullptr;
    }

    // SpriteAnimation animation = m_animationPresets[preset_id];
    std::shared_ptr<SpriteAnimation> ptr = std::make_shared<SpriteAnimation>(m_animationPresets[preset_id]);

    // assert(animation.frames.size() != 0);

    if (addToList) {
        m_animations.push_back(ptr);
    }

    return ptr;
}

/// *******************************************************************
///
/// updateAnimations
///
/// *******************************************************************

void AnimationManager::updateAnimations(float deltaTime)
{

    for (auto& animation : m_animations) {
        if (animation->isFinished || animation->type == AnimationType::Manual) {
            continue;
        }

        animation->ticksSinceLastUpdate += deltaTime * 1000;
        if (animation->ticksSinceLastUpdate >= animation->ticksPrFrame) {

            animation->ticksSinceLastUpdate = 0;

            // When playing forward
            if (animation->direction == AnimationDirection::Forward) {

                animation->currentFrame++;

                // If we have reached the last frame...
                if (animation->currentFrame == animation->numberOfFrames) {

                    // Loop, restart or stop the m_animation according to AnimationType.
                    if (animation->type == AnimationType::PlayOnce) {
                        animation->isFinished = true;
                        animation->currentFrame--;
                        continue;
                    } else if (animation->type == AnimationType::Loop) {
                        animation->currentFrame = 0;
                        continue;
                    } else if (animation->type == AnimationType::PingPong) {
                        animation->direction = AnimationDirection::Reverse;
                        animation->currentFrame -= 2;
                        if (animation->currentFrame < 0)
                            animation->currentFrame = 0; // For single-frame animations, which when subtracting 2 frames ends at -1
                        continue;
                    }
                }

            } else {

                // When playing reverse...

                animation->currentFrame--;

                // If we have reached the first frame...
                if (animation->currentFrame < 0) {
                    // Loop, restart or stop the m_animation according to AnimationType.
                    if (animation->type == AnimationType::PlayOnce) {
                        animation->currentFrame = 0;
                        animation->isFinished = true;
                        continue;
                    } else if (animation->type == AnimationType::Loop) {
                        animation->currentFrame = animation->numberOfFrames - 1;
                        continue;
                    } else if (animation->type == AnimationType::PingPong) {
                        animation->direction = AnimationDirection::Forward;
                        animation->currentFrame = 1;

                        continue;
                    }
                }
            }
        }
    }
}

void AnimationManager::destroyAnimation(const std::shared_ptr<SpriteAnimation>& animation) { m_animations.remove(animation); }

std::map<std::string_view, SpriteAnimation> AnimationManager::getAllPresets() { return m_animationPresets; }

}
