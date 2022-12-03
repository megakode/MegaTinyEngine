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
#include <utility>

#include "BoxCollider.h"
#include "Base.h"
#include "AnimationManager.h"
#include "GameObjects/GameObject.h"
#include "KinematicBody.h"
#include "Texture.hpp"

namespace Engine {

    class Sprite;
    typedef std::shared_ptr<Sprite> SpritePtr;

    class Sprite : public GameObject, public BoxCollider {

    public:

        Sprite( const std::shared_ptr<Texture>& texture = nullptr );

        static SpritePtr createWithTexture( const std::string& textureId );
        static SpritePtr createWithAnimation(const std::string& animationId);


        ~Sprite();

        void setAnimation( const std::string& id );

        // GameObject overrides

        void update(float timeSinceLast ) override;
        void draw( SDL_Renderer *renderer ) override;

        // Collision

        Rect bbox() override;

        // Physics
        void setVelocity( const Vec2f& velocity );
        void setAcceleration( const Vec2f& vec );
        void setFriction( float friction );
        void setKinematicBodyPosition( const Vec2f& pos );

        bool isKinematicsEnabled() const;
        void setKinematicsEnabled( bool enabled );

        void setDebugDraw(bool enabled);

        /// Set a sprites alpha value used when rendering the texture
        ///
        /// \param alpha value between 0.0-1.0
        void setAlpha( float alpha );

        /// Get a sprites alpha value used when rendering the texture
        ///
        /// \return alpha value between 0.0-1.0
        float getAlpha();

        /// Get the current textureRect. If an animation is playing this will change with the animation. If not, this will be the full size of the texture.
        const Rect & textureRect();

        Vec2f scaling = {1.0f,1.0f};

        void setCurrentFrame(int frameNum);

        void setTexture(  const std::shared_ptr<Texture>& texture );

        std::shared_ptr<Texture> texture();

    protected:

        std::shared_ptr<SpriteAnimation> m_currentAnimation = nullptr;

        Rect m_textureRect;
        KinematicBody m_kinematicBody;

        bool m_kinematicsEnabled = false;

        bool m_debugDraw = false;
        float m_alpha = 1.0f;


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
