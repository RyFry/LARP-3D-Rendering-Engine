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
    btScalar _jump_speed;
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

    PhysicsPlayerController(PhysicsWorld* physics_world,
                            btVector3 initial_position = btVector3(0, 0, 0),
                            btScalar forward_speed = .03,
                            btScalar backward_speed = .01, btScalar strafe_speed = .02,
                            btScalar jump_speed = 5.0, btScalar max_slope = .872665); // 50 degrees in radians
    void update_movement(PhysicsWorld* world, PlayerDirection direction);
    void rotate(btQuaternion rotation_amount);
    void jump();
    void set_user_pointer(void * user_pointer);
    void step(PhysicsWorld* world, btScalar delta_time);
    void * get_user_pointer();
    btVector3 get_position() const;
    btQuaternion get_orientation() const;
};
