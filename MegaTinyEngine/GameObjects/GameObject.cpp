//
//  GameObject.cpp
//  SDLTest
//
//  Created by Peter Bone on 19/05/2020.
//  Copyright © 2020 megakode. All rights reserved.
//

#include "GameObject.h"
#include <algorithm>
#include <assert.h>
#include <iostream>

namespace Engine {

GameObject::GameObject() { }

GameObject::~GameObject() { }

/// ***************************************************************
/// Children
/// ***************************************************************

void GameObject::addChild(const std::shared_ptr<GameObject>& child)
{
    // Maybe we should use a raw pointer for the parent instead (i've seen this recommended for trees, as there should never be a parentless child, so no dangling )
    child->parent = this;
    child->setWorldPositionIsDirtyRecursively(true);
    children.insert(child);
}

// ***************************************************************
// Position
// ***************************************************************

void GameObject::setWorldPositionIsDirtyRecursively(bool isDirty)
{
    this->isWorldPositionDirty = isDirty;

    for (auto child : children) {
        child->setWorldPositionIsDirtyRecursively(isDirty);
    }
}

//
// Set local position
//

void GameObject::setLocalPosition(int x, int y)
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
    if (!isWorldPositionDirty) {
        return worldPosition;
    } else {
        // If we are a root node: world position = local position
        if (parent == nullptr) {
            isWorldPositionDirty = false;
            worldPosition = localPosition;
            return worldPosition;
        }

        Vec2i parentPos = parent->getWorldPosition();

        worldPosition = { parentPos.x + localPosition.x, parentPos.y + localPosition.y };
        isWorldPositionDirty = false;
        return worldPosition;
    }
}

const Vec2i& GameObject::getLocalPosition() const { return localPosition; }

int GameObject::getX() const { return localPosition.x; }

int GameObject::getY() const { return localPosition.y; }

//
// Set local position
//

void GameObject::setLocalPosition(const Vec2i& position) { setLocalPosition(position.x, position.y); }

///
/// Update
///

void GameObject::update(float ticksSinceLast)
{
    // Override in subclasses
    for (const auto& child : children) {
        child->update(ticksSinceLast);
    }

    // A child might become null during iteration of children, as one child might remove another during update.
    // So we use defered deletion to be safe.
    for(const auto& child : children_to_delete)
    {
        children.erase(child);
    }
}

///
/// Draw
///

void GameObject::draw(SDL_Renderer* renderer)
{
    assert(renderer);
    for (const auto& child : children) {
        child->draw(renderer);
    }
}

///
/// Handle Event
///

bool GameObject::handleEvent(const InputEvent& event)
{
    for (auto& iter : children) {
        if (iter.get()->handleEvent(event)) {
            return true;
        }
    }
    return false;
}

const std::unordered_set<std::shared_ptr<GameObject>>& GameObject::getChildren() { return children; }

void GameObject::removeChild(GameObjectPtr object)
{
    assert(object);
    children_to_delete.insert(object);

}

void GameObject::removeFromParent()
{
    if (parent != nullptr) {
        parent->removeChild(shared_from_this());
        parent = nullptr;
    }
}

void GameObject::removeAllChildren() { children.clear(); }

bool GameObject::isVisible() const { return m_isVisible; }

void GameObject::setVisible(bool isVisible) { m_isVisible = isVisible; }

}