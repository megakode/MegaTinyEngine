//
// Created by Peter Bone on 22/06/2020.
//

#include "TextNode.h"
#include "Core.h"
namespace Engine {

    TextNode::TextNode(const std::string& textureName, char firstCharacter, char lastCharacter , unsigned int characterWidth, unsigned int characterHeight ) {

        m_texture = Core::textureCache()->getTextureWithIdentifier(textureName);
        m_first_character = firstCharacter;
        m_last_character = lastCharacter;
        m_character_width = (int)characterWidth;
        m_character_height = (int)characterHeight;
    }

    std::shared_ptr<TextNode> TextNode::create()
    {
        auto font = Core::fontManager()->getDefaultFont();
        return std::make_shared<TextNode>(font.texture,' ','z',font.charWidth,font.charHeight);
    }


    void TextNode::setText( const std::string& text ){
        m_text = text;
    }

    void TextNode::draw(SDL_Renderer *renderer) {

        //Draw the m_texture
        Vec2i wp = getWorldPosition();

        for( int i = 0 ; i < m_text.size() ; i++ ){

            SDL_Rect dstRect = {wp.x+i*m_character_width, wp.y, m_character_width, m_character_height };
            SDL_Rect srcRect {0,0,m_character_width,m_character_height};

            char currentChar = m_text[i];

            // Skip if the font doesn't contain the current character
            if( currentChar < m_first_character || currentChar > m_last_character){
                continue;
            }

            currentChar = currentChar - m_first_character;
            srcRect.x = currentChar * m_character_width;

            SDL_RenderCopy(renderer,m_texture->Get(),&srcRect,&dstRect);

        }

        for( const auto& child : children ){
            child->draw(renderer);
        }
    }

}