//
//  TextureCache.cpp
//  SDLTest
//
//  Created by Peter Bone on 26/05/2020.
//  Copyright © 2020 megakode. All rights reserved.
//

#include <SDL_image.h>
#include <iostream>
#include "TextureCache.h"
#include <cassert>

namespace Engine {

    TextureCache::TextureCache(SDL_Renderer *renderer) : m_renderer(renderer)
    {
        
    }

    std::shared_ptr<Texture> TextureCache::loadTexture( const std::string& absoluteFileNameWithPath, const std::string& identifier )
    {
        assert(m_renderer != nullptr);
        SDL_Texture *sdl_texture;

        sdl_texture = IMG_LoadTexture(m_renderer, (absoluteFileNameWithPath.c_str()));

        if (sdl_texture == nullptr) {
            std::cerr << SDL_GetError();
            throw std::runtime_error(SDL_GetError());
        }

        auto texture = std::make_shared<Texture>(sdl_texture);
        m_textures[identifier] = texture;

        std::cout << "Texture loaded: " << identifier << " size=" << std::to_string(texture->getWidth()) << "x" << std::to_string(texture->getHeight()) << std::endl;

        return texture;

    }

    std::shared_ptr<Texture> TextureCache::getTextureWithIdentifier( const std::string& identifier )
    {
        return m_textures[identifier];
    }

    std::map<std::string, std::shared_ptr<Texture>> TextureCache::getAllTextures() {
        return m_textures;
    }

}