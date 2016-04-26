#pragma once

#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <iostream>

#include "PhysicsWorld.hpp"

class PhysicsPlayerController
{
private:
    btTransform _transform; // Initialize this to player's transform
    btPairCachingGhostObject* _ghost_object;
    btKinematicCharacterController* _char_controller;
    btScalar _forward_speed;
    btScalar _backward_speed;
    btScalar _strafe_speed;
    btScalar _jump_height;
    btScalar _max_slope;
public:
    enum PlayerDirection
    {
        STOP,
        LEFT,
        RIGHT,
        FORWARD,
        BACKWARD
    };

    PhysicsPlayerController(PhysicsWorld* physics_world, btVector3 initial_position = btVector3(0, 0, 0), 
                            btScalar fwdspeed = .15, btScalar bwdspeed = .1, btScalar strspeed = .13,
                            btScalar jmpheight = .1, btScalar mxslope = .872665);
    void update_movement(PhysicsWorld* world, PlayerDirection direction);
    void rotate(btScalar rotation_amount);
    void jump();
    void set_user_pointer(void * user_pointer);
    void step(PhysicsWorld* world, btScalar delta_time);
    void * get_user_pointer();
    btVector3 get_position() const;
    btQuaternion get_orientation() const;
};
