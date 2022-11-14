//
// Created by peter on 25/07/2020.
//

#ifndef __LAYER_H
#define __LAYER_H

#include "MegaTinyEngine/GameObjects/GameObject.h"
#include "MegaTinyEngine/Texture.hpp"

namespace Engine {

    class Layer : public GameObject {
        public:

        int layerId;

        enum class BackgroundTextureStyle {
            Normal,
            TileHorizontal,
            TileVertical,
            TileBoth,
            Stretch
        };


        ColorRGBA8 backgroundColor = {0,0,0,0};

        std::shared_ptr<Texture> backgroundTexture = nullptr;

        BackgroundTextureStyle backgroundTextureStyle = BackgroundTextureStyle::Normal;

        explicit Layer( int layerId ) : layerId(layerId) {};

        Layer( int layerId, ColorRGBA8 backgroundColor ){
            this->layerId = layerId;
            this->m_useBackgroundColor = true;
            this->backgroundColor = backgroundColor;
        }

        Layer( int layerId, const std::shared_ptr<Texture>& backgroundTexture , BackgroundTextureStyle style )
        {
            this->layerId = layerId;
            this->backgroundTexture = backgroundTexture;
            this->backgroundTextureStyle = style;
        }
        void draw(SDL_Renderer *renderer) override;

      private:

        bool m_useBackgroundColor = false;

    };

}


#endif //__LAYER_H
