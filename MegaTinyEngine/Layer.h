//
// Created by peter on 25/07/2020.
//

#ifndef SIMPLEWESTERNGAME_LAYER_H
#define SIMPLEWESTERNGAME_LAYER_H

#include "GameObject.h"

namespace Engine {

    class Layer : public GameObject {
        public:
        int layerId;

        Layer( int layerId ) : layerId(layerId) {};

    };

}


#endif //SIMPLEWESTERNGAME_LAYER_H
