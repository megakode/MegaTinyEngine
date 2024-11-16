//
//  Sprite.hpp
//  SDLTest
//
//  Created by Peter Bone on 20/05/2020.
//  Copyright © 2020 megakode. All rights reserved.
//

#ifndef Sprite_h
#define Sprite_h

#include "SDL.h"
#include <map>
#include <memory>
#include <stdio.h>
#include <string_view>
#include <utility>

#include "AnimationManager.h"
#include "Base.h"
#include "BoxCollider.h"
#include "GameObjects/GameObject.h"
#include "KinematicBody.h"
#include "Texture.hpp"

namespace Engine {

class Sprite;
typedef std::shared_ptr<Sprite> SpritePtr;

class Sprite : public GameObject, public BoxCollider {

public:

    enum class Origin {
        UpperLeft,
        UpperCenter,
        UpperRight,
        CenterLeft,
        Center,
        CenterRight,
        LowerLeft,
        LowerCenter,
        LowerRight
    };


    Sprite(const std::shared_ptr<Texture>& texture = nullptr);

    static SpritePtr createWithTexture(const std::string_view& textureId);
    static SpritePtr createWithAnimation(const std::string_view& animationId);

    void setAnimation(const std::string_view& id);

    // GameObject overrides

    void update(float timeSinceLast) override;
    void draw(SDL_Renderer* renderer) override;

    // Collision

    Rect bbox() override;

    // Physics
    void setVelocity(const Vec2f& velocity);
    void setAcceleration(const Vec2f& vec);
    void setFriction(float friction);
    void setKinematicBodyPosition(const Vec2f& pos);

    bool isKinematicsEnabled() const;
    void setKinematicsEnabled(bool enabled);

    void setDebugDraw(bool enabled);

    /// Get the current textureRect. If an animation is playing this will change with the animation. If not, this will be the full size of the texture.
    const Rect& textureRect();

    void setCurrentFrame(int frameNum);

    void setTexture(const std::shared_ptr<Texture>& texture);

    std::shared_ptr<Texture> texture();

    /**
     * Set a sprites alpha value used when rendering the texture
     * @param alpha value between 0.0-1.0
     */
    void setAlpha(float alpha);

    /**
     * Get a sprites alpha value used when rendering the texture
     * @return alpha value between 0.0-1.0
     */
    float getAlpha();

    void setRotation(float degree);

    /**
     * Define the center point from which a sprite is drawn. 
     * Default it is 0,0.
     * Max is sprite width and height.
     */
    void setOrigin(const Vec2i& origin);

    /**
     * Define the center point from which a sprite is drawn. 
     * Default it is UpperLeft.
     */
    void setOrigin( Origin origin );

    /**
     * Get a sprites origin point. (the center point from where the sprite is drawn)
     */
    const Vec2f& getOrigin() const;

    /**
     * Set a sprites scale factor.
     * @param scaling
     */
    void setScaling(const Vec2f& scaling);

    /**
     * Get a sprites scale factor.
     */
    const Vec2f& getScaling() const;

protected:
    std::shared_ptr<SpriteAnimation> m_currentAnimation = nullptr;

    Rect m_textureRect;
    KinematicBody m_kinematicBody;

    float m_rotation = 0;

    bool m_kinematicsEnabled = false;

    bool m_debugDraw = false;

    Vec2f m_scaling { 1.0f, 1.0f };

    float m_alpha = 1.0f;
    
    Vec2i m_origin;

    void updateTextureRect();

    ///
    /// Sets a bounding box with a size that equals the same as the sprites texture rect (a single animation frame)
    ///
    void setDefaultBBox();

    void setBBox(int xoffset, int yoffset, int width, int height);

private:
    Rect m_bbox;

    std::shared_ptr<Texture> m_texture;
};

}

#endif /* Sprite_h */
