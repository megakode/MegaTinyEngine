//
//  Sprite.cpp
//  SDLTest
//
//  Created by Peter Bone on 20/05/2020.
//  Copyright © 2020 megakode. All rights reserved.
//

#include <iostream>
#include "Sprite.h"
#include "SDL.h"
#include "Core.h"

namespace Engine {

    Sprite::Sprite( const std::shared_ptr<Texture>& texture )
    {
        m_currentAnimation = nullptr;
        m_texture = texture;
    }

    Sprite::~Sprite( ){
    }

    void Sprite::setDefaultBBox()
    {
        auto wp = getWorldPosition();
        m_bbox = { wp.x , wp.y , m_textureRect.width , m_textureRect.height };
    }

    /// Set the sprite bounding box
    /// \param xoffset relative xoffset to the sprite origin
    /// \param yoffset relative yoffset to the sprite origin
    /// \param width  box width
    /// \param height box height
    void Sprite::setBBox( int xoffset, int yoffset, int width, int height ){
        m_bbox = {xoffset,yoffset,width,height};
    }

    ///
    /// Get the sprites bounding box
    /// \return The bounding box in world coordinates
    ///
    Rect Sprite::bbox(){
        auto wp = getWorldPosition();
        return {wp.x + m_bbox.x , wp.y + m_bbox.y , m_bbox.width , m_bbox.height };
    }

    const Rect& Sprite::textureRect()
    {
        updateTextureRect(); // Just to be sure it is set. Otherwise it is set for the first time in update()
        return m_textureRect;
    }


    void Sprite::updateTextureRect()
    {

        if( m_currentAnimation == nullptr ){

            // default to a full texture rect
            m_textureRect = { 0,0, m_texture->getWidth(), m_texture->getHeight() };

        } else {

            SpriteFrame *currentFrame = m_currentAnimation->getCurrentFrame();

            m_textureRect.x = currentFrame->x;
            m_textureRect.y = currentFrame->y;
            m_textureRect.width = currentFrame->w;
            m_textureRect.height = currentFrame->h;

        }
    }

    ///
    /// Visibility
    ///

    void Sprite::setVisible( bool visible ){
        m_visible = visible;
    }

    bool Sprite::isVisible(){
        return m_visible;
    }

    ///
    /// Play Animation
    ///

    void Sprite::playAnimation( const std::string& id )
    {
        if(m_currentAnimation!= nullptr){
            Core::animationManager()->destroyAnimation(m_currentAnimation);
        }

        m_currentAnimation = Core::animationManager()->createAnimation(id);

        updateTextureRect();

        if(m_bbox.isZeroSize()){
            setDefaultBBox();
        }
    }


    ///
    /// update
    ///

    void Sprite::update(float timeSinceLast )
    {
        updateTextureRect();

        // Set sprite position to our simulated kinematic body position

        if(m_kinematicsEnabled)
        {
            if(m_kinematicBody.velocity.x != 0 || m_kinematicBody.velocity.y != 0)
            {
                GameObject::setLocalPosition( (int)m_kinematicBody.position.x , (int)m_kinematicBody.position.y );
            }

            m_kinematicBody.update(timeSinceLast);
        }

        GameObject::update(timeSinceLast);
    }

    ///
    /// Draw
    ///

    void Sprite::draw(SDL_Renderer *renderer)
    {
        if(m_visible)
        {
            //Draw the m_texture
            Vec2i wp = getWorldPosition();
            SDL_Rect srcRect = {m_textureRect.x,m_textureRect.y,m_textureRect.width,m_textureRect.height};
            SDL_Rect dstRect = {wp.x, wp.y, m_textureRect.width,m_textureRect.height };
            SDL_Point p {0,0};

            SDL_SetTextureAlphaMod(m_texture->Get(), m_alpha*255);
            SDL_RenderCopyEx(renderer, m_texture->Get(), &srcRect, &dstRect, 0, &p, SDL_FLIP_NONE);

            if(m_debugDraw){
                // Draw dst rect
                SDL_SetRenderDrawColor(renderer,0,255,0,1);
                SDL_RenderDrawRect(renderer,&dstRect);
                // Draw bbox
                SDL_Rect bboxRect = {bbox().x,bbox().y,bbox().width,bbox().height};
                SDL_SetRenderDrawColor(renderer,255,0,0,1);
                SDL_RenderDrawRect(renderer,&bboxRect);
            }
        }

        GameObject::draw(renderer);
    }

    ///
    /// Kinematics
    ///

    bool Sprite::isKinematicsEnabled() const
    {
        return m_kinematicsEnabled;
    }

    void Sprite::setKinematicsEnabled( bool enabled )
    {
        m_kinematicsEnabled = enabled;
        if(enabled){
            m_kinematicBody.position = static_cast<Vec2f>(getLocalPosition());
        }
    }

    void Sprite::setVelocity(const Vec2f& velocity)
    {
        m_kinematicBody.applyForce(velocity);
    }

    void Sprite::setAcceleration(const Vec2f &vec)
    {
        m_kinematicBody.setAcceleration(vec);
    }

    void Sprite::setFriction( float friction )
    {
        m_kinematicBody.friction = friction;
    }

    void Sprite::setDebugDraw(bool enabled)
    {
        m_debugDraw = enabled;
    }

    void Sprite::setKinematicBodyPosition(const Vec2f& pos)
    {
        m_kinematicBody.position = pos;
        GameObject::setLocalPosition( (int)m_kinematicBody.position.x , (int)m_kinematicBody.position.y );
    }

    void Sprite::setAlpha( float alpha )
    {
        m_alpha = alpha;
    }

}
