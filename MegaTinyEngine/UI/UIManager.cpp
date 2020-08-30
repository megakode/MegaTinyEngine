//
// Created by peter on 30/08/2020.
//

#include <algorithm>
#include <iterator>
#include "UIManager.h"
#include "Button.h"

namespace Engine {

    void UIManager::handleInput(InputEvent event)
    {


        if(event.deviceType == InputDeviceType::Mouse && event.state == InputKeyState::Moved){

            // Så slipper vi for at blande alle Sprites der flytter sig rundt med UI widgets som vi kun vil skyde muse-rays på.
            auto newColliders = Core::collisionManager()->ray({static_cast<int>(event.position.x),static_cast<int>(event.position.y)}, UICollisionGroupID);
            decltype(newColliders) addedColliders;
            decltype(newColliders) removedColliders;

            // Calculate which colliders were added and removed since we moved the mouse last,
            // and thus building a list of colliders to receive a mouseEnter and mouseExit event.

            // last - current = removed
            // current - last = added
            std::set_difference(m_mouseOverColliders.begin(), m_mouseOverColliders.end(), newColliders.begin(), newColliders.end(),std::inserter(removedColliders, removedColliders.begin()));
            std::set_difference(newColliders.begin(), newColliders.end(), m_mouseOverColliders.begin(), m_mouseOverColliders.end(),std::inserter(addedColliders, addedColliders.begin()));

            m_mouseOverColliders = newColliders;

            // Mouse enter on an objects collider

            for( const auto& collider : addedColliders ){
                auto house = dynamic_cast<Button*>(collider.get());
                if(house){
                    house->setHighlight(true);
                }
            }

            // Mouse exit on an objects collider

            for( const auto& collider : removedColliders ){
                auto house = dynamic_cast<Button*>(collider.get());
                if(house){
                    house->setHighlight(false);
                }
            }
        }

        // Left mouse button pressed over a collider
        /*
        if(event.deviceType == InputDeviceType::Mouse && event.state == InputKeyState::Pressed && event.key == InputKey::MouseButtonLeft){
            for( const auto& collider : m_mouseOverColliders ){
                auto house = dynamic_cast<Button*>(collider.get());
                if(house){
                    house->setHighlight(true);
                }
            }
        }
         */
    }

}
