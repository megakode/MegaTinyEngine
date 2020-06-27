//
// Created by Peter Bone on 19/06/2020.
//

#include <iostream>
#include "CollisionManager.h"

namespace Engine {

    void CollisionManager::addCollider( BoxCollider* collider ) {
        m_objects.push_back(collider);
    }

    void CollisionManager::removeCollider( BoxCollider* collider ) {

        auto it = std::find(m_objects.begin(),m_objects.end(),collider);

        if(it!=m_objects.end()){
            m_objects.erase(it);
        }
    }

    void CollisionManager::doCollisionChecks() {

        std::vector<Rect> boxes;
        boxes.reserve(m_objects.size() );

        for( auto obj : m_objects ){
            boxes.push_back( obj->bbox() );
        }

        for( int i = 0 ; i < boxes.size()-1 ; i++ ){
            for( int j = i+1 ; j < boxes.size() ; j++){
                //std::cout << "checking element " << i << "-" << j << std::endl;
                if( (m_objects[i]->collision_mask_bits & m_objects[j]->collision_mask_bits) && boxes[i].intersects(boxes[j])){
                    auto a = m_objects[i];
                    auto b = m_objects[j];

                    if(m_listener != nullptr){
                        m_listener->collisionManagerDetectedCollisionBetween(a,b);
                    }

                    // Do this last, as it potentially deletes the object on collision
                    a->onCollide(b);

                }
            }
        }

    }

    void CollisionManager::setListener(ICollisionManagerListener* listener) {
        m_listener = listener;
    }

}