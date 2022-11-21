//
// Created by peter on 06/09/2020.
//

#include "FontManager.h"

namespace Engine
{
    void FontManager::addFont(const FontDefinition& fontDef )
    {
        fonts.emplace_back(fontDef);
    }

    FontDefinition FontManager::getDefaultFont()
    {
        assert(!fonts.empty()); // No fonts loaded

        return fonts.front();
    }
}