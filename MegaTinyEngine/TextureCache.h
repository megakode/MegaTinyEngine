//
//  TextureCache.hpp
//  SDLTest
//
//  Created by Peter Bone on 26/05/2020.
//  Copyright © 2020 megakode. All rights reserved.
//

#ifndef TextureCache_h
#define TextureCache_h

#include <stdio.h>
#include <string>
#include <memory>
#include <map>

#include "Texture.hpp"

namespace Engine {

    class TextureCache {

        std::map<std::string , std::shared_ptr<Texture>> m_textures;
        SDL_Renderer *m_renderer = nullptr;

    public:

        TextureCache(SDL_Renderer *renderer);

        ///
        /// \brief Loads a m_texture from disk into m_texture memory and stores them in a map with the fileName (excluding the path) as key.
        /// \returns A shared pointer to the newly loaded `m_texture`.

        std::shared_ptr<Texture> loadTexture( const std::string& absoluteFileNameWithPath, const std::string& identifier );

        ///
        /// \brief gets a m_texture with the given identifier from the cache
        /// \returns a shared pointer to the `Texture` object found in cache, or `nullptr` if no m_texture with the given identifier is found.

        std::shared_ptr<Texture> getTextureWithIdentifier( const std::string& identifier );

        ///
        /// Get all textures in cache
        /// \return a map with <texture identifier , texture*>
        ///
        std::map<std::string , std::shared_ptr<Texture>> getAllTextures();


    };

}

#endif /* TextureCache_h */
