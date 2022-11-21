//
// Created by peter on 06/09/2020.
//

#ifndef SIMPLEWESTERNGAME_FONTMANAGER_H
#define SIMPLEWESTERNGAME_FONTMANAGER_H

#include "MegaTinyEngine/Resources/ResourceFile.h"

namespace Engine
{

    class FontManager
    {
        public:

            FontManager() = default;

            void addFont(const FontDefinition& fontDef );

            /**
             * Gets the first font in the list
             * @return A FontDefinition
             */
            FontDefinition getDefaultFont();

        private:

            std::list<FontDefinition> fonts;

    };

}

#endif //SIMPLEWESTERNGAME_FONTMANAGER_H
