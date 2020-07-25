//
// Created by peter on 15/07/2020.
//

#include <iostream>
#include "Button.h"

namespace Engine{

    Button::Button(const std::string &animationPresetId ,  int tag )  {

        m_currentAnimation = Core::animationManager()->createAnimation(animationPresetId,false);

        if(m_currentAnimation == nullptr){
            std::cerr << "Trying to create a button with an animationPreset that is not found in AnimationManager: " << animationPresetId << std::endl;
            assert(1);
        }

        setTexture( Engine::Core::textureCache()->getTextureWithIdentifier(m_currentAnimation->textureId) );
        setDefaultBBox();

        m_tag = tag;

        //Core::collisionManager()->addCollider(enable_shared_from_this<Engine::Button>::shared_from_this());
        // TODO: find a way to remove collider when we are destroyed
    }

    void Button::setHighlight(bool highlighted) {
        m_highlighted = highlighted;
    }

    void Button::draw(SDL_Renderer *renderer) {

        SDL_BlendMode oldBlendMode;

        Sprite::draw(renderer);

        if (m_highlighted) {

            SDL_GetTextureBlendMode(texture()->Get(),&oldBlendMode);
            SDL_SetTextureBlendMode(texture()->Get(),SDL_BLENDMODE_ADD);
            setAlpha(0.2);

            Sprite::draw(renderer);

            SDL_SetTextureBlendMode(texture()->Get(),oldBlendMode);

            setAlpha(1);
        }


    }

    bool Button::handleEvent(const InputEvent &event) {
        if(event.key == InputKey::MouseButtonLeft && event.state == InputKeyState::Pressed){
            Rect b = bbox();
            if( b.intersects({(int)event.position.x,(int)event.position.y,1,1})){
                setCurrentFrame(1);
                return true;
            }
        } else if(event.key == InputKey::MouseButtonLeft && event.state == InputKeyState::Released ){
            Rect b = bbox();
            setCurrentFrame(0);
            if( b.intersects({(int)event.position.x,(int)event.position.y,1,1})){
                if(m_callback != nullptr){
                    m_callback(m_tag);
                }
            }
        }
        return false;
    }


}