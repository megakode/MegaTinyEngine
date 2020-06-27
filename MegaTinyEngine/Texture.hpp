//
//  Texture.hpp
//  SDLTest
//
//  Created by Peter Bone on 19/05/2020.
//  Copyright © 2020 megakode. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <string>
#include <SDL.h>

namespace Engine {

    class Texture {

    public:

        Texture(SDL_Texture *texture);
        ~Texture();

        int getWidth() const;
        int getHeight() const;

        // Returns the managed SDL_Texture
        SDL_Texture* Get() const;

    private:

        SDL_Texture *m_texture; // Unmanaged SDL_texture (that we are now managing)

        int width;
        int height;

        ///
        /// Update the m_width/m_height parameters from the m_texture
        ///
        void updateWidthHeight();

    };

}


#endif /* Texture_hpp */
