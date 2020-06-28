//
// Created by Peter Bone on 24/06/2020.
//

#ifndef SDLTEST_RESOURCELOADER_H
#define SDLTEST_RESOURCELOADER_H

#include <string>
#include "Vendor/json.hpp"
#include "MegaTinyEngine/Animation.h"

namespace Engine {

    class ResourceLoader {

    public:

        static void loadFromJSON(std::string jsonFileName);

        static void saveAnimations( std::string filename );

        static std::string getResourcePath(const std::string &subDir = "");
    };

}


#endif //SDLTEST_RESOURCELOADER_H
