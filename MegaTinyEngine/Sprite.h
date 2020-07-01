//
//  Sprite.hpp
//  SDLTest
//
//  Created by Peter Bone on 20/05/2020.
//  Copyright © 2020 megakode. All rights reserved.
//

#ifndef Sprite_h
#define Sprite_h

#include <memory>
#include <utility>
#include <stdio.h>
#include <map>
#include "Rect.h"
#include "Collision/BoxCollider.h"
#include "SDL.h"

#include "Texture.hpp"
#include "GameObject.h"
#include "AnimationManager.h"
#include "KinematicBody.h"

namespace Engine {

    class Sprite : public GameObject, public BoxCollider {

    public:

        Sprite( const std::shared_ptr<Texture>& texture = nullptr );

        ~Sprite();

        void playAnimation( const std::string& id );

        // GameObject overrides

        void update(float timeSinceLast ) override;
        void draw( SDL_Renderer *renderer ) override;

        // Collision

        Rect bbox() override;
        void onCollide(BoxCollider *other) override;

        // Physics
        void setVelocity( const Vec2f& velocity );
        void setAcceleration( const Vec2f& vec );
        void setFriction( float friction );
        void setKinematicBodyPosition( const Vec2f& pos );

        bool isKinematicsEnabled() const;
        void setKinematicsEnabled( bool enabled );

        void setDebugDraw(bool enabled);

        /// Set whether to draw the Sprite or not
        /// \param visible draw if true
        void setVisible(bool visible);

        /// Whether the Sprite is drawn or not
        bool isVisible();

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

    protected:

        std::shared_ptr<SpriteAnimation> m_currentAnimation;
        std::shared_ptr<Texture> m_texture;
        Rect m_textureRect;
        Rect m_bbox;
        KinematicBody m_kinematicBody;

        bool m_visible = true;
        bool m_kinematicsEnabled = false;

        bool m_debugDraw = false;
        float m_alpha = 1.0f;


        void updateTextureRect();

        ///
        /// Sets a bounding box with a size that equals the same as the sprites texture rect (a single animation frame)
        ///
        void setDefaultBBox();

        void setBBox(int xoffset, int yoffset, int width, int height);


    };

}

#endif /* Sprite_h */
