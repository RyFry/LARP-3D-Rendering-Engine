#pragma once

#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <iostream>

#include "Larp/LarpPrerequisites.hpp"
#include "Larp/Node.hpp"
#include "World.hpp"

namespace Physics
{
    class PlayerController
    {
    private:
        GLfloat m_width;
        GLfloat m_height;
        GLfloat m_depth;
        btPairCachingGhostObject* m_ghost_object;
        btKinematicCharacterController* m_char_controller;
        GLfloat m_forward_speed;
        GLfloat m_backward_speed;
        GLfloat m_strafe_speed;
        GLfloat m_jump_speed;
        GLfloat m_max_slope;
        uint8_t m_directions;
        bool m_on_floor;
    public:
        enum PlayerDirection
        {
            STOP = 0,
            LEFT = 1,
            RIGHT = 2,
            FORWARD = 4,
            BACKWARD = 8
        };

        PlayerController(World* physics_world, const Larp::Node* node,
                         GLfloat width, GLfloat height, GLfloat depth,
                         glm::vec3 initial_position = glm::vec3(0, 0, 0),
                         GLfloat forward_speed = .03,
                         GLfloat backward_speed = .01, GLfloat strafe_speed = .02,
                         GLfloat jump_speed = 3.0, GLfloat max_slope = .872665); // 50 degrees in radians
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
         * @param world The World object that this object is tracked by.
         * @note After this function is called, the PlayerController's direction is
         *       set to STOP
         */
        void update_movement(World* world);
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
         * Steps the player in the World it is associated with
         * @param world The World object that is tracking this PlayerController
         * @param delta_time The time between this update and the last update
         */
        void step(World* world, GLfloat delta_time);
        /**
         * @return The user pointer attached to this object
         */
        Larp::Node* get_user_pointer();
        /**
         * @return The position of this PlayerController in the World
         */
        glm::vec3 get_position() const;
        void set_position(glm::vec3 position);
        /**
         * @return The orientation of this PlayerController in the World
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
        /**
         * @return The width of this Player's btRigidBody
         */
        GLfloat get_width() const;
        GLfloat get_height() const;
        GLfloat get_depth() const;

        bool is_on_floor() const;

        bool is_moving() const;
    };
}
