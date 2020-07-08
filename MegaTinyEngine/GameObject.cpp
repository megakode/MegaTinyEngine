//
//  GameObject.cpp
//  SDLTest
//
//  Created by Peter Bone on 19/05/2020.
//  Copyright © 2020 megakode. All rights reserved.
//

#include "GameObject.h"
#include <iostream>
#include <assert.h>
#include <algorithm>

namespace Engine {

    GameObject::GameObject()
    {

    }

    GameObject::~GameObject()
    {
    }

    /// ***************************************************************
    /// Children
    /// ***************************************************************

    void GameObject::addChild(const std::shared_ptr<GameObject>& child)
    {
        // Maybe we should use a raw pointer for the parent instead (i've seen this recommended for trees, as there should never be a parentless child, so no dangling )
        child->parent = this;
        children.push_back(child);
    }

    // ***************************************************************
    // Position
    // ***************************************************************

    void GameObject::setWorldPositionIsDirtyRecursively( bool isDirty )
    {
        this->isWorldPositionDirty = isDirty;

        for ( auto child : children)
        {
            child->setWorldPositionIsDirtyRecursively(isDirty);
        }
    }

    //
    // Set local position
    //

    void GameObject::setLocalPosition( int x, int y )
    {
        localPosition.x = x;
        localPosition.y = y;
        setWorldPositionIsDirtyRecursively(true);
    }

    //
    // Get world position
    //

    Vec2i GameObject::getWorldPosition()
    {
        if(!isWorldPositionDirty){
            return worldPosition;
        } else {
            // If we are a root node: world position = local position
            if(parent==nullptr){
                isWorldPositionDirty = false;
                worldPosition = localPosition;
                return worldPosition;
            }

            Vec2i parentPos = parent->getWorldPosition();

            worldPosition = { parentPos.x + localPosition.x , parentPos.y + localPosition.y};
            isWorldPositionDirty = false;
            return worldPosition;
        }
    }

    const Vec2i &GameObject::getLocalPosition() const {
        return localPosition;
    }


    int GameObject::getX() const
    {
        return localPosition.x;
    }

    int GameObject::getY() const
    {
        return localPosition.y;
    }

    //
    // Set local position
    //

    void GameObject::setLocalPosition(const Vec2i &position)
    {
        setLocalPosition(position.x,position.y);
    }

    ///
    /// Update
    ///

    void GameObject::update(float ticksSinceLast)
    {
        // Override in subclasses
        for( const auto& child : children ){
            // A child might become null during iteration of children, as one child might remove another during update.
            if(child!=nullptr)child->update(ticksSinceLast);
        }
    }

    ///
    /// Draw
    ///

    void GameObject::draw( SDL_Renderer *renderer )
    {
        assert(renderer);
        for( const auto& child : children ){
            child->draw(renderer);
        }
    }

    ///
    /// Handle Event
    ///

    bool GameObject::handleEvent(const InputEvent& event) {
        return false;
    }

    const std::vector<std::shared_ptr<GameObject>>& GameObject::getChildren() {
        return children;
    }


    void GameObject::removeChild( GameObject *object ){
        assert(object);
        auto it = std::find_if(children.begin(),children.end(),
                    [&](const auto& val){ return val.get() == object; } );

        if(it != children.end()){
            children.erase(it);
        } else {
            // not found!?
        }

    }

    void GameObject::removeFromParent() {
        if(parent!= nullptr){
            parent->removeChild(this);
        }
    }

    void GameObject::removeAllChildren()
    {
        children.clear();
    }

}