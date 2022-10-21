//
// Created by Peter Bone on 25/06/2020.
//

#ifndef RESOURCEFILE_H
#define RESOURCEFILE_H

#include "MegaTinyEngine/Animation.h"
#include "MegaTinyEngine/UI/FontDefinition.h"
#include <filesystem>
#include <list>
#include <map>
#include <string>

namespace Engine
{
struct ResourceFile
{
    std::filesystem::path baseDirectory;
    std::list<std::string> textureFileNames;
    std::map<std::string, SpriteAnimation> animations;
    std::list<FontDefinition> fontDefinitions;
};

} // namespace Engine

#endif