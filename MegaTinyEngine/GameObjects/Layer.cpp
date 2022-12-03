//
// Created by peter on 25/07/2020.
//

#include "Layer.h"
#include "Core.h"

namespace Engine
{


void Layer::draw(SDL_Renderer *renderer)
{
    if(m_useBackgroundColor){
        SDL_SetRenderDrawColor(renderer,backgroundColor.r,backgroundColor.g,backgroundColor.b,backgroundColor.a);
        SDL_RenderClear(renderer);
    }

    if(backgroundTexture != nullptr){

        int width = backgroundTexture->getWidth();
        int height = backgroundTexture->getHeight();
        int windowWidth = Core::getLogicalWindowSize().width;
        int windowHeight = Core::getLogicalWindowSize().height;
        Vec2i wp = getWorldPosition();
        SDL_Rect srcRect = {0,0,width,height};

        switch (backgroundTextureStyle)
        {
        case BackgroundTextureStyle::Normal:{
            SDL_Rect dstRect = {wp.x,wp.y,width,height};
            SDL_SetTextureAlphaMod(backgroundTexture->Get(), 255);
            SDL_RenderCopy(renderer,backgroundTexture->Get(),&srcRect, &dstRect);
            break;
        }

        case BackgroundTextureStyle::Stretch:{
            SDL_Rect dstRect = {wp.x,wp.y,windowWidth,windowHeight};
            SDL_RenderCopy(renderer,backgroundTexture->Get(),&srcRect, &dstRect);
            break;
        }

        case BackgroundTextureStyle::TileHorizontal:
            for(int i = 0 ; i < (windowWidth/width)+1 ; i++ ){
                SDL_Rect dstRect = {wp.x + i*width,wp.y,width,height};
                SDL_RenderCopy(renderer,backgroundTexture->Get(),&srcRect, &dstRect);
            }
            break;
        case BackgroundTextureStyle::TileVertical:
            for(int i = 0 ; i < (windowHeight/height)+1 ; i++ ){
                SDL_Rect dstRect = {wp.x,wp.y+i*height,width,height};
                SDL_RenderCopy(renderer,backgroundTexture->Get(),&srcRect, &dstRect);
            }
            break;
        case BackgroundTextureStyle::TileBoth:
            for(int x = 0 ; x < (windowWidth/width)+1 ; x++ ){
                for(int y = 0 ; y < (windowHeight/height)+1 ; y++ ){
                    SDL_Rect dstRect = { wp.x + x*width, wp.y + y*height, width, height };
                    SDL_RenderCopy(renderer,backgroundTexture->Get(),&srcRect, &dstRect);
                }
            }
            break;
        }
    }

    GameObject::draw(renderer);
}

}