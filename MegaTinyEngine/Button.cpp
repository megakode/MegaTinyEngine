//
// Created by peter on 15/07/2020.
//

#include "Button.h"

namespace Engine{

    Button::Button(const std::string &textureIdentifier , int tag ) {
        setTexture( Engine::Core::textureCache()->getTextureWithIdentifier(textureIdentifier) );

        m_tag = tag;
        setDefaultBBox();
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
        if(event.deviceType == InputDeviceType::Mouse && event.key == InputKey::MouseButtonLeft ){
            Rect b = bbox();
            if( b.intersects({(int)event.position.x,(int)event.position.y,1,1})){
                if(m_callback != nullptr){
                    m_callback(m_tag);
                }
            }
        }
        return GameObject::handleEvent(event);
    }


}