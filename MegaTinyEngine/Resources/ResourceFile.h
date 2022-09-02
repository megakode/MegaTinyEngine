//
// Created by Peter Bone on 25/06/2020.
//

#ifndef RESOURCEFILE_H
#define RESOURCEFILE_H

#include <list>
#include <string>
#include <map>
#include "MegaTinyEngine/Animation.h"
#include "MegaTinyEngine/UI/FontDefinition.h"

namespace Engine
{
    struct ResourceFile
    {
        std::list<std::string> textureFileNames;
        std::map<std::string,SpriteAnimation> animations;
        std::list<FontDefinition> fontDefinitions;
    };

}

#endif