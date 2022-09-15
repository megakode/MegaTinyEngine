//
// Created by Peter Bone on 24/06/2020.
//

#ifndef SDLTEST_RESOURCELOADER_H
#define SDLTEST_RESOURCELOADER_H

#include "MegaTinyEngine/Animation.h"
#include "ResourceFile.h"
#include "Vendor/json.hpp"
#include <string>

namespace Engine
{

class ResourceLoader
{

  public:
    static bool loadResourceFile(const std::string &path, ResourceFile &resourceFile);

    static bool loadResources(const std::string &jsonFileName);

    static void saveAnimations(std::string filename);

  private:
};

} // namespace Engine

#endif // SDLTEST_RESOURCELOADER_H
