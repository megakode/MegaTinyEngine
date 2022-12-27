//
// Created by Peter Bone on 19/06/2020.
//

#include "CollisionManager.h"
#include "Base.h"
#include "CollisionInfo.h"
#include <algorithm>
#include <iostream>

namespace Engine {

    void CollisionManager::addCollider( const std::shared_ptr<BoxCollider>& collider ) {
        m_objects.push_back(collider);
    }

    void CollisionManager::removeCollider( const std::shared_ptr<BoxCollider>& collider ) {

        auto it = std::find(m_objects.begin(),m_objects.end(),collider);

        if(it!=m_objects.end()){
            m_objects.erase(it);
        }
    }

    std::vector<std::shared_ptr<BoxCollider>> CollisionManager::ray( const Vec2i& at , int collision_group_id ){

        std::vector<std::shared_ptr<BoxCollider>> colliders;
        Rect mouseRect = {at.x,at.y,1,1};

        for( auto object : m_objects ) {
            if (collision_group_id == -1 || collision_group_id == object->collision_group_id) {
                if (object->bbox().intersects(mouseRect)) {
                    colliders.push_back(object);
                }
            }
        }


        return colliders;

    }

    void CollisionManager::doCollisionChecks() {

        std::vector<Rect> boxes;
        boxes.reserve(m_objects.size() );

        for( auto obj : m_objects ){
            boxes.push_back( obj->bbox() );
        }

        std::vector<CollisionInfo> collisions;

        for( int i = 0 ; i < std::max(0,(int)boxes.size()-1) ; i++ ){
            for( int j = i+1 ; j < boxes.size() ; j++){
                //std::cout << "checking element " << i << "-" << j << std::endl;
                if( (m_objects[i]->collision_mask_bits & m_objects[j]->collision_mask_bits) && boxes[i].intersects(boxes[j])){
                    auto a = m_objects[i];
                    auto b = m_objects[j];
                    collisions.emplace_back(CollisionInfo{a,b});
                }
            }
        }

        for( auto& collision : collisions){
            if(m_listener != nullptr){
                m_listener->collisionManagerDetectedCollisionBetween(collision.first,collision.second);
            }

            for( auto& group_listener : m_collisionGroupListeners ){
                if(collision.first->collision_group_id == group_listener.collision_group_a ) {
                    if (collision.second->collision_group_id == group_listener.collision_group_b) {
                        group_listener.callback(collision.first,collision.second);
                    }
                } else if( collision.second->collision_group_id == group_listener.collision_group_a ) {
                    if (collision.first->collision_group_id == group_listener.collision_group_b) {
                        group_listener.callback(collision.second,collision.first);
                    }
                }
            }

            // Do this last, as it potentially deletes the object on collision
            //a->onCollide(b);

        }

    }

    void CollisionManager::setListener(ICollisionManagerListener* listener) {
        m_listener = listener;
    }

    void CollisionManager::addListener(int collision_group_a, int collision_group_b, std::function<void(const std::shared_ptr<BoxCollider>&, const std::shared_ptr<BoxCollider>&)> callback) {
        m_collisionGroupListeners.push_back({ collision_group_a,collision_group_b, std::move(callback) });
    }

    }