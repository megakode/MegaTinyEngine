//
// Created by Peter Bone on 22/06/2020.
//

#include "TextNode.h"
#include "Core.h"
namespace Engine
{

TextNode::TextNode(const std::string &textureName, char firstCharacter, char lastCharacter, unsigned int characterWidth, unsigned int characterHeight)
{

    m_texture = Core::textureCache()->getTextureWithIdentifier(textureName);
    m_first_character = firstCharacter;
    m_last_character = lastCharacter;
    m_character_width = (int)characterWidth;
    m_character_height = (int)characterHeight;
}

std::shared_ptr<TextNode> TextNode::createWithTexture(const std::string &textureName, char firstCharacter, char lastCharacter, unsigned int characterWidth, unsigned int characterHeight)
{
    return std::make_shared<TextNode>(textureName, firstCharacter, lastCharacter, characterWidth, characterHeight);
}

std::shared_ptr<TextNode> TextNode::createWithDefaultFont()
{
    auto font = Core::fontManager()->getDefaultFont();
    return std::make_shared<TextNode>(font.texture, font.firstCharacter, font.lastCharacter, font.charWidth, font.charHeight);
}

void TextNode::setText(const std::string &text)
{
    m_text = text;
}

void TextNode::draw(SDL_Renderer *renderer)
{
    if(!m_isVisible){
        return;
    }
    // Draw the m_texture
    Vec2i wp = getWorldPosition();
    int startx = wp.x;
    int starty = wp.y;

    if (alignment == TextNodeAlignment::Center)
    {
        startx -= m_text.size() * m_character_width / 2;
    }
    else if (alignment == TextNodeAlignment::Right)
    {
        startx -= m_text.size() * m_character_width;
    }

    for (int i = 0; i < m_text.size(); i++)
    {

        SDL_Rect dstRect = {startx + i * m_character_width, starty, m_character_width, m_character_height};
        SDL_Rect srcRect{0, 0, m_character_width, m_character_height};

        char currentChar = m_text[i];

        // Skip if the font doesn't contain the current character
        if (currentChar < m_first_character || currentChar > m_last_character)
        {
            continue;
        }

        currentChar = currentChar - m_first_character;
        srcRect.x = currentChar * m_character_width;

        // TODO: Implement alpha on text nodes. Render with the following line:
        // SDL_SetTextureAlphaMod(m_texture->Get(), m_alpha * 255);
        SDL_RenderCopy(renderer, m_texture->Get(), &srcRect, &dstRect);
    }

    for (const auto &child : children)
    {
        child->draw(renderer);
    }
}

} // namespace Engine
