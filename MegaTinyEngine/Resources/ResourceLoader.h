//
// Created by Peter Bone on 24/06/2020.
//

#pragma once

#include "ResourceFile.h"
#include <string_view>

namespace Engine {

class ResourceLoader {

public:
    static bool loadResourceFile(const std::string_view& path, ResourceFile& resourceFile);

    static bool loadResources(const std::string_view& jsonFileName);

    static void saveAnimations(std::string_view filename);

private:
};

} // namespace Engine
