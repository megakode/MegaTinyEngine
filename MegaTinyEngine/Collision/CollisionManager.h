//
// Created by Peter Bone on 19/06/2020.
//

#ifndef SDLTEST_COLLISIONMANAGER_H
#define SDLTEST_COLLISIONMANAGER_H

#include "MegaTinyEngine/Base.h"
#include "MegaTinyEngine/GameObjects/Sprite.h"
#include <vector>

namespace Engine {

    class ICollisionManagerListener {
    public:
        virtual void collisionManagerDetectedCollisionBetween( const std::shared_ptr<BoxCollider>& firstObject , const std::shared_ptr<BoxCollider>& secondObject ) = 0;
    };

    class CollisionManager {

    public:

        ///
        /// Add item to list of colliders being checked for collision, every time 'doCollisionChecks' is called.
        /// \param collider to add
        ///
        void addCollider( const std::shared_ptr<BoxCollider>& collider );

        ///
        /// Remove item from list of colliders being checked for collision, every time 'doCollisionChecks' is called.
        /// \param collider to add
        ///
        void removeCollider( const std::shared_ptr<BoxCollider>& collider );

        ///
        /// Do collision checks on all added BoxColliders, and notify them by calling the 'onCollide()' BoxCollider interface method.
        ///
        void doCollisionChecks();


        /// Shoots a ray into the screen and detects which objects it hits. Useful for doing mouse over collision.
        /// \param at the point at which to shoot a ray, in world coordinates.
        /// \param collision_group_id id of the collision group to filter by. (Disables filter with default value of -1)
        /// \return A vector of colliders which were hit by the ray.
        std::vector<std::shared_ptr<BoxCollider>> ray( const Vec2i& at , int collision_group_id = -1 );

        ///
        /// Set listener to be called whenever a collision occurs
        /// Apart from this listener, the individual elements who are colliding are also called using their 'onCollide' method.
        ///
        void setListener( ICollisionManagerListener* listener );

    private:

        ICollisionManagerListener *m_listener = nullptr;
        std::vector<std::shared_ptr<BoxCollider>> m_objects;

    };

}

#endif //SDLTEST_COLLISIONMANAGER_H
