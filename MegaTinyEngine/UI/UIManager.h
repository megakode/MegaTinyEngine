//
// Created by peter on 30/08/2020.
//

#ifndef SIMPLEWESTERNGAME_UIMANAGER_H
#define SIMPLEWESTERNGAME_UIMANAGER_H

#include <vector>
#include <MegaTinyEngine/Collision/BoxCollider.h>
#include "MegaTinyEngine/InputManager.h"

namespace Engine {

    constexpr int UICollisionGroupID = 999'999'999;

class UIManager
{
    public:

        UIManager() = default;

        void handleInput( InputEvent event );

    private:

        std::vector<std::shared_ptr<BoxCollider>> m_mouseOverColliders;
};

}


#endif //SIMPLEWESTERNGAME_UIMANAGER_H
