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
    /**
     * Adds a movement direction to this PlayerControl for the next call
     * to update_movement().
     * @param direction The direction to add to the already specified directions
     * @note If a direction is added twice before the next call update_movement,
     *       nothing happens
     */
    void add_movement_direction(PlayerDirection direction);
    /**
     * Updates this PlayerController's movement based on the directions specified
     * by add_movement_direction().
     * @param world The PhysicsWorld object that this object is tracked by.
     * @note After this function is called, the PlayerController's direction is
     *       set to STOP
     */
    void update_movement(PhysicsWorld* world);
    /**
     * Rotates this PlayerController
     * @param rotation_amount The quaternion amount to rotate this PlayerController
     */
    void rotate(glm::quat rotation_amount);
    /**
     * Tells this PlayerController to jump
     */
    void jump();
    /**
     * Changes the user pointer of this object.
     * @param user_pointer The pointer that this object should reference and
     *                     have attached to it.
     */
    void set_user_pointer(void * user_pointer);
    /**
     * Steps the player in the PhysicsWorld it is associated with
     * @param world The PhysicsWorld object that is tracking this PlayerController
     * @param delta_time The time between this update and the last update
     */
    void step(PhysicsWorld* world, GLfloat delta_time);
    /**
     * @return The user pointer attached to this object
     */
    Larp::NodePtr get_user_pointer();
    /**
     * @return The position of this PlayerController in the PhysicsWorld
     */
    glm::vec3 get_position() const;
    /**
     * @return The orientation of this PlayerController in the PhysicsWorld
     */
    glm::quat get_orientation() const;
    /**
     * @return The direction that this PlayerController is facing
     */
    glm::vec3 get_direction() const;
    /**
     * @return The yaw of this PlayerController
     */
    GLfloat get_yaw() const;
    /**
     * @return The pitch of this PlayerController
     * @warning This function may not work
     */
    GLfloat get_pitch() const;
    /**
     * @return The roll of this PlayerController
     * @warning This function may not work
     */
    GLfloat get_roll() const;
};
