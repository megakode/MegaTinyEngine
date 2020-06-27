//
// Created by Peter Bone on 06/06/2020.
//

#include "Core.h"
#include "Sprite.h"

namespace Engine {

    AnimationManager* Core::m_animationManager;
    TextureCache* Core::m_textureCache;
    InputManager* Core::m_inputManager;
    CollisionManager* Core::m_collisionManager;
    SDL_Renderer* Core::m_renderer;

    bool Core::init( SDL_Renderer *renderer ) {

        m_animationManager = new AnimationManager();
        m_textureCache = new TextureCache(renderer);
        m_inputManager = new InputManager();
        m_collisionManager = new CollisionManager();
        m_renderer = renderer;

        return true;
    }

    std::shared_ptr<Sprite> Core::createSprite(const std::string& textureId, const std::string& animationId){

        auto texture = m_textureCache->getTextureWithIdentifier(textureId);
        assert(texture);
        auto sprite = std::make_shared<Sprite>(texture);


        if(!animationId.empty()){
            sprite->playAnimation(animationId);
        }

        return sprite;
    }

    /*
    std::shared_ptr<Sprite> Core::createSprite(const std::string& textureId ){
        auto sprite = std::make_shared<Sprite>(Core::getInstance().textureCache()->getTextureWithIdentifier("taco"));
        return sprite;
    }
    */
    AnimationManager* Core::animationManager() {
        return m_animationManager;
    }

    TextureCache* Core::textureCache() {
        return m_textureCache;
    }

    InputManager *Core::inputManager() {
        return m_inputManager;
    }

    CollisionManager *Core::collisionManager() {
        return m_collisionManager;
    }

    Rect Core::getLogicalWindowSize() {
        if(m_renderer != nullptr ){
            Rect size;
            SDL_RenderGetLogicalSize(m_renderer,&size.width,&size.height);
            return size;
        } else {
            return {0,0,0,0};
        }
    }


}
