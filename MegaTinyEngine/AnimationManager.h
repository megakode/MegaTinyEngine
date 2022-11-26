//
// Created by Peter Bone on 29/05/2020.
//

#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <memory>
#include <map>
#include <list>
#include "Animation.h"

namespace Engine{

class AnimationManager {

public:

    void addAnimationPreset(const std::string& id, const SpriteAnimation& animation);

    /// Creates an animation from a preset and adds it to internal list of animations to update and keep track of.
    /// \param preset_id Id of the animation preset to use. Must be added with 'addAnimationPreset' first. Done automatically by ResourceLoader when loading JSON resources.
    /// \param addToList Whether to add the created animation to the internal list of animations, that are updated on each call to AnimationManager::update(). Default: true.
    /// \return A shared pointer to the created animation.
    std::shared_ptr<SpriteAnimation> createAnimation(const std::string& preset_id, bool addToList = true );

    /// Delete an animation from the internal list.
    /// \param animation to remove
    void destroyAnimation(const std::shared_ptr<SpriteAnimation>& animation);

    void updateAnimations( float deltaTime );

    std::map<std::string,SpriteAnimation> getAllPresets();

private:

    /// When an animation is requested with 'createAnimation', a lookup in this map is performed with the animation name as key,
    /// and the found animation is then copied into the m_animations list where it is updated continously until destroyed with 'destroyAnimation'.

    std::map<std::string,SpriteAnimation> m_animationPresets;

    // This is the collection with both heavy iteration and insertion/removal load on,
    // so keep an eye on the performance of this as the game grows,
    // and consider refactoring it to another collection type (e.g. Vector or one backed by a custom allocator)

    std::list<std::shared_ptr<SpriteAnimation>> m_animations;


};

}

#endif //ANIMATIONMANAGER_H
