//
//  Texture.cpp
//  SDLTest
//
//  Created by Peter Bone on 19/05/2020.
//  Copyright © 2020 megakode. All rights reserved.
//

#include <cassert>
#include <iostream>
#include "Texture.hpp"
#include "Base.h"

namespace Engine {

    Texture::Texture(SDL_Texture *texture) {
        assert(texture);
        m_texture = texture;
        updateWidthHeight();
    }


    Texture::~Texture() {
        std::cout << "dealloc Texture \n";
        if (m_texture != nullptr) {
            SDL_DestroyTexture(m_texture);
        }
    }

///
/// Get SDL_Texture
///

    SDL_Texture *Texture::Get() const {
        return m_texture;
    }

///
/// Get m_height
///

    int Texture::getWidth() const {
        return width;
    }

///
/// Get m_width
///

    int Texture::getHeight() const {
        return height;
    }

///
/// Private
///

    void Texture::updateWidthHeight() {
        if (m_texture != nullptr) {
            uint32_t format;
            int access;
            SDL_QueryTexture(m_texture, &format, &access, &width, &height);
        } else {
            width = 0;
            height = 0;
        }

    }

}