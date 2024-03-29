//
// Created by Peter Bone on 24/06/2020.
//

#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include "Animation.h"
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

#endif // RESOURCELOADER_H
