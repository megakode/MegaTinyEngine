//
//  Sprite.cpp
//
//  Created by Peter Bone on 20/05/2020.
//  Copyright © 2020 megakode. All rights reserved.
//

#include "Sprite.h"
#include "Base.h"
#include "Core.h"
#include "SDL.h"
#include <iostream>

namespace Engine {

SpritePtr Sprite::createWithTexture(const std::string_view& textureId)
{
    auto texture = Core::textureCache()->getTextureWithIdentifier(textureId);
    assert(texture);
    auto sprite = std::make_shared<Sprite>(texture);

    return sprite;
}

SpritePtr Sprite::createWithAnimation(const std::string_view& animationId)
{
    auto spr = std::make_shared<Sprite>();
    spr->setAnimation(animationId);
    return spr;
}

Sprite::Sprite(const std::shared_ptr<Texture>& texture)
{
    setTexture(texture);
    setDefaultBBox();
}

void Sprite::setDefaultBBox()
{
    auto wp = getWorldPosition();
    m_bbox = { wp.x, wp.y, m_textureRect.width, m_textureRect.height };
}

/// Set the sprite bounding box
/// \param xoffset relative xoffset to the sprite origin
/// \param yoffset relative yoffset to the sprite origin
/// \param width  box width
/// \param height box height
void Sprite::setBBox(int xoffset, int yoffset, int width, int height) { m_bbox = { xoffset, yoffset, width, height }; }

///
/// Get the sprites bounding box
/// \return The bounding box in world coordinates
///
Rect Sprite::bbox()
{
    auto wp = getWorldPosition();
    return { wp.x + m_bbox.x, wp.y + m_bbox.y, m_bbox.width, m_bbox.height };
}

const Rect& Sprite::textureRect() { return m_textureRect; }

void Sprite::updateTextureRect()
{
    if (m_texture == nullptr) {
        return;
    }

    if (m_currentAnimation == nullptr) {

        // default to a full texture rect
        m_textureRect = { 0, 0, m_texture->getWidth(), m_texture->getHeight() };

    } else {

        SpriteFrame* currentFrame = m_currentAnimation->getCurrentFrame();

        m_textureRect.x = currentFrame->x;
        m_textureRect.y = currentFrame->y;
        m_textureRect.width = currentFrame->w;
        m_textureRect.height = currentFrame->h;
    }
}

void Sprite::setCurrentFrame(int frameNum)
{
    if (m_currentAnimation != nullptr) {
        m_currentAnimation->currentFrame = std::max(0, std::min(frameNum, (int)m_currentAnimation->frames.size() - 1));
        updateTextureRect();
    }
}

///
/// Play Animation
///

void Sprite::setAnimation(const std::string_view& id)
{
    if (m_currentAnimation != nullptr) {
        Core::animationManager()->destroyAnimation(m_currentAnimation);
    }

    m_currentAnimation = Core::animationManager()->createAnimation(id);

    assert(m_currentAnimation);

    auto animationTexture = Core::textureCache()->getTextureWithIdentifier(m_currentAnimation->textureId);

    assert(animationTexture);

    setTexture(animationTexture);

    if (m_bbox.isZeroSize()) {
        setDefaultBBox();
    }
}

///
/// update
///

void Sprite::update(float timeSinceLast)
{
    updateTextureRect(); // removing this will break animation

    // Set sprite position to our simulated kinematic body position

    if (m_kinematicsEnabled) {
        if (m_kinematicBody.velocity.x != 0 || m_kinematicBody.velocity.y != 0) {
            GameObject::setLocalPosition((int)m_kinematicBody.position.x, (int)m_kinematicBody.position.y);
        }

        m_kinematicBody.update(timeSinceLast);
    }

    GameObject::update(timeSinceLast);
}

///
/// Draw
///

void Sprite::draw(SDL_Renderer* renderer)
{
    if (m_isVisible) {
        float scaledWidth = m_scaling.x * m_textureRect.width;
        float scaledHeight = m_scaling.y * m_textureRect.height;
        // Draw the m_texture
        Vec2i wp = getWorldPosition();
        SDL_Rect srcRect = { m_textureRect.x, m_textureRect.y, m_textureRect.width, m_textureRect.height };
        SDL_Rect dstRect = { wp.x, wp.y, (int)scaledWidth, (int)scaledHeight };
        SDL_Point p { 0, 0 };

        SDL_SetTextureAlphaMod(m_texture->Get(), m_alpha * 255);
        SDL_RenderCopyEx(renderer, m_texture->Get(), &srcRect, &dstRect, 0, &p, SDL_FLIP_NONE);

        if (m_debugDraw) {
            // Draw dst rect
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);
            SDL_RenderDrawRect(renderer, &dstRect);
            // Draw bbox
            SDL_Rect bboxRect = { bbox().x, bbox().y, bbox().width, bbox().height };
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
            SDL_RenderDrawRect(renderer, &bboxRect);
        }
    }

    GameObject::draw(renderer);
}

///
/// Kinematics
///

bool Sprite::isKinematicsEnabled() const { return m_kinematicsEnabled; }

void Sprite::setKinematicsEnabled(bool enabled)
{
    m_kinematicsEnabled = enabled;
    if (enabled) {
        m_kinematicBody.position = static_cast<Vec2f>(getLocalPosition());
    }
}

void Sprite::setVelocity(const Vec2f& velocity) { m_kinematicBody.applyForce(velocity); }

void Sprite::setAcceleration(const Vec2f& vec) { m_kinematicBody.setAcceleration(vec); }

void Sprite::setFriction(float friction) { m_kinematicBody.friction = friction; }

void Sprite::setDebugDraw(bool enabled) { m_debugDraw = enabled; }

void Sprite::setKinematicBodyPosition(const Vec2f& pos)
{
    m_kinematicBody.position = pos;
    GameObject::setLocalPosition((int)m_kinematicBody.position.x, (int)m_kinematicBody.position.y);
}

void Sprite::setTexture(const std::shared_ptr<Texture>& texture)
{
    m_texture = texture;
    updateTextureRect();
}

std::shared_ptr<Texture> Sprite::texture() { return m_texture; }

void Sprite::setAlpha(float alpha) { m_alpha = alpha; }

float Sprite::getAlpha() { return m_alpha; }

void Sprite::setScaling(const Vec2f& scaling) { m_scaling = scaling; }

const Vec2f& Sprite::getScaling() const { return m_scaling; }

}
