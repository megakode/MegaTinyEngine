//
// Created by Peter Bone on 25/06/2020.
//

#ifndef SDLTEST_RESOURCEFILE_H
#define SDLTEST_RESOURCEFILE_H

#endif //SDLTEST_RESOURCEFILE_H

#include <list>
#include <string>
#include <map>
#include "Animation.h"

namespace Engine{

    struct ResourceFile {

        std::list<std::string> textureFileNames;
        std::map<std::string,SpriteAnimation> animations;

    };

}