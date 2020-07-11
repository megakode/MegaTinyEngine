//
// Created by Peter Bone on 20/06/2020.
//

#ifndef SDLTEST_KINEMATICBODY_H
#define SDLTEST_KINEMATICBODY_H


#include "Base.h"

namespace Engine {

    struct KinematicBody {

        Vec2f position;
        Vec2f velocity;
        Vec2f accel;
        float max_velocity = 1000;
        float friction = 0.95;

        void update( float deltaTime ){

            velocity.x += accel.x * deltaTime;
            velocity.y += accel.y * deltaTime;

            if(velocity.x < -max_velocity)velocity.x = -max_velocity;
            if(velocity.x > max_velocity)velocity.x = max_velocity;
            if(velocity.y < -max_velocity)velocity.y = -max_velocity;
            if(velocity.y > max_velocity)velocity.y = max_velocity;

            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;

            velocity.x *= friction;
            velocity.y *= friction;


        }

        void setAcceleration( const Vec2f& a ){
            accel.x = a.x;
            accel.y = a.y;
        }

        void setVelocity( const Vec2f& v ){
            velocity.x = v.x;
            velocity.y = v.y;
        }

        void applyForce( const Vec2f& force ){
            velocity.x += force.x;
            velocity.y += force.y;
        }

    };


}

#endif //SDLTEST_KINEMATICBODY_H
