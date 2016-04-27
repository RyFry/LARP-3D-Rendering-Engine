#pragma once

#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <iostream>

#include "LarpPrerequisites.hpp"
#include "Node.hpp"
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
    uint8_t _directions;
public:
    enum PlayerDirection
    {
        STOP = 0,
        LEFT = 1,
        RIGHT = 2,
        FORWARD = 4,
        BACKWARD = 8
    };

    PhysicsPlayerController(PhysicsWorld* physics_world, const Larp::NodePtr node,
                            btVector3 initial_position = btVector3(0, 0, 0),
                            btScalar forward_speed = .03,
                            btScalar backward_speed = .01, btScalar strafe_speed = .02,
                            btScalar jump_speed = 5.0, btScalar max_slope = .872665); // 50 degrees in radians
    void add_movement_direction(PlayerDirection direction);
    void update_movement(PhysicsWorld* world);
    void rotate(btQuaternion rotation_amount);
    void jump();
    void set_user_pointer(void * user_pointer);
    void step(PhysicsWorld* world, btScalar delta_time);
    Larp::NodePtr get_user_pointer();
    glm::vec3 get_position() const;
    glm::quat get_orientation() const;
    glm::vec3 get_direction() const;
    GLfloat get_yaw() const;
};
