#pragma once

#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include "PhysicsWorld.hpp"

class PhysicsPlayerController
{
private:
    btTransform _transform; // Initialize this to player's transform
    btPairCachingGhostObject* _ghost_object;
    btKinematicCharacterController* _char_controller;
public:
    enum PlayerDirection
    {
        LEFT,
        RIGHT,
        FOWARD,
        BACKWARD
    };

    PhysicsPlayerController(PhysicsWorld* physics_world, btVector3 initial_position);
void move(PhysicsWorld* world, btScalar delta_time, PlayerDirection direction);
    void rotate(btScalar rotation_amount);
};
