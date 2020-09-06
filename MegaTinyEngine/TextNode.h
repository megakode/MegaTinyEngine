//
// Created by Peter Bone on 22/06/2020.
//

#ifndef SDLTEST_TEXTNODE_H
#define SDLTEST_TEXTNODE_H


#include "GameObject.h"
#include "Texture.hpp"

namespace Engine {

    class TextNode : public GameObject {

    public:

        static std::shared_ptr<TextNode> create();

        void draw(SDL_Renderer *renderer) override;

        void setText(const std::string &text);

        TextNode(const std::string& textureName, char firstCharacter, char lastCharacter , unsigned int characterWidth, unsigned int characterHeight );

    private:

        std::shared_ptr<Texture> m_texture;
        int m_character_width;
        int m_character_height;
        char m_first_character;
        char m_last_character;

        std::string m_text;
    };

}

#endif //SDLTEST_TEXTNODE_H
