//
// Created by peter on 06/09/2020.
//

#ifndef SIMPLEWESTERNGAME_FONTDEFINITION_H
#define SIMPLEWESTERNGAME_FONTDEFINITION_H

namespace Engine
{
    struct FontDefinition
    {
        std::string texture;
        int charWidth;
        int charHeight;
        char firstCharacter;
        char lastCharacter;
    };
}

#endif //SIMPLEWESTERNGAME_FONTDEFINITION_H
