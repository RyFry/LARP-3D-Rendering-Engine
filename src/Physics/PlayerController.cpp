#include "PlayerController.hpp"

namespace Physics
{
    PlayerController::PlayerController(World* physics_world, const Larp::Node* node,
                                       GLfloat width, GLfloat height, GLfloat depth,
                                       glm::vec3 initial_position, GLfloat forward_speed,
                                       GLfloat backward_speed, GLfloat strafe_speed,
                                       GLfloat jump_speed, GLfloat max_slope)
        : m_width(width),
          m_height(height),
          m_depth(depth),
          m_forward_speed(forward_speed),
          m_backward_speed(backward_speed),
          m_strafe_speed(strafe_speed),
          m_jump_speed(jump_speed),
          m_max_slope(max_slope),
          m_directions(0)
    {
        // Create player shape
        btScalar radius((width + depth) / 4.0);
        btCapsuleShape* player_shape = new btCapsuleShape(radius, height);

        // Init player ghost object
        m_ghost_object = new btPairCachingGhostObject();
        btTransform transform = m_ghost_object->getWorldTransform();
        transform.setOrigin(btVector3(initial_position.x, initial_position.y, initial_position.z));

        m_ghost_object->setWorldTransform(transform);

        // Set the shape and collision object type
        m_ghost_object->setCollisionShape(player_shape);
        m_ghost_object->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

        // Setup the character controller and add it to the physics world
        m_char_controller =
            new btKinematicCharacterController(m_ghost_object, player_shape, 0.0);
        m_char_controller->setGravity(btVector3(0.0, 4.9, 0.0));
        m_char_controller->setMaxSlope(max_slope);
        m_char_controller->setJumpSpeed(jump_speed);
        physics_world->get_dynamics_world()->addCollisionObject(
            m_ghost_object,
            btBroadphaseProxy::CharacterFilter,
            btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);
        physics_world->get_dynamics_world()->addAction(m_char_controller);
        m_ghost_object->setUserPointer(nullptr);
    }

    void PlayerController::add_movement_direction(PlayerController::PlayerDirection direction)
    {
        m_directions |= direction;
    }

    void PlayerController::update_movement(World* world)
    {
        // For finding movement vectors:
        //   forward X up = right
        //   up X forward = left
        /*
          And the great thing about transformation matrices, is that this 3x3 orientation sub-matrix
          itself consists of three normalized vectors.
          Turns out, the first column is the vector pointing to the right (positive X axis).
          The column to the right of that is the 'up vector' (positive Y).
          The column next to that, is the vector pointing rearward or forward depending on your
          camera orientation convention (positive Z axis).
          https://www.opengl.org/discussion_boards/showthread.php/175515-Get-Direction-from-Transformation-Matrix-or-Quat
        */
        btVector3 btFrom = m_ghost_object->getWorldTransform().getOrigin();
        btVector3 btTo(btFrom.x(), btFrom.y() - 5.0f, btFrom.z());
        btCollisionWorld::ClosestRayResultCallback res(btFrom, btTo);

        world->get_dynamics_world()->rayTest(btFrom, btTo, res); // m_btWorld is btDiscreteDynamicsWorld

        // Raycast so that we can prevent sliding when on slopes
        if(res.hasHit() && (btFrom.y() - res.m_hitPointWorld.y()) < 0.55f)
        {
            m_char_controller->setGravity(btVector3(0.0, 0.0, 0.0));
            m_on_floor = true;
        }
        else
        {
            m_char_controller->setGravity(btVector3(0.0, 4.9, 0.0));
            m_on_floor = false;
        }

        btVector3 movement_direction(0.0f, 0.0f, 0.0f);

        // if (m_directions == PlayerDirection::STOP && m_char_controller->onGround())
        // {
        //     m_char_controller->setGravity(0.0);
        //     // m_char_controller->setWalkDirection(movement_direction);
        //     // return;
        // }
        // else
        // {
        //     m_char_controller->setGravity(4.9);
        // }

        btScalar matrix[16];
        m_ghost_object->getWorldTransform().getOpenGLMatrix(matrix);

        uint8_t dirs = m_directions;
        if ((dirs & PlayerDirection::FORWARD) != 0)
        {
            btVector3 forward(matrix[8], matrix[9], matrix[10]);
            movement_direction += forward * m_forward_speed;
        }
        if ((dirs & PlayerDirection::BACKWARD) != 0)
        {
            btVector3 forward(matrix[8], matrix[9], matrix[10]);
            movement_direction += forward * -m_backward_speed;
        }
        if ((dirs & PlayerDirection::LEFT) != 0)
        {
            btVector3 forward(matrix[8], matrix[9], matrix[10]);
            forward *= m_strafe_speed;
            btVector3 left = btVector3(0, 1, 0).cross(forward);
            movement_direction += left;
        }
        if ((dirs & PlayerDirection::RIGHT) != 0)
        {
            btVector3 forward(matrix[8], matrix[9], matrix[10]);
            forward *= m_strafe_speed;
            btVector3 right = forward.cross(btVector3(0, 1, 0));
            movement_direction += right;
        }

        m_char_controller->setWalkDirection(movement_direction);
        m_directions = STOP;
    }

    void PlayerController::rotate(glm::quat orientation_amount)
    {
        btTransform trans = m_ghost_object->getWorldTransform();
        btQuaternion quat = trans.getRotation();
        btQuaternion rot(orientation_amount.w, orientation_amount.x, orientation_amount.y, orientation_amount.z);
        quat = rot * quat;
        trans.setRotation(quat);
        m_ghost_object->setWorldTransform(trans);
    }

    void PlayerController::jump()
    {
        m_char_controller->setGravity(btVector3(0.0, 4.9, 0.0));
        m_char_controller->jump();
    }

    void PlayerController::set_user_pointer(void * user_pointer)
    {
        m_ghost_object->setUserPointer(user_pointer);
    }

    void PlayerController::step(World* world, GLfloat delta_time)
    {
        m_char_controller->playerStep(world->get_dynamics_world(), delta_time);
    }

    Larp::Node* PlayerController::get_user_pointer()
    {
        return static_cast<Larp::Node*>(m_ghost_object->getUserPointer());
    }

    glm::vec3 PlayerController::get_position() const
    {
        btVector3 vec(m_ghost_object->getWorldTransform().getOrigin());
        return glm::vec3(vec.x(), vec.y(), vec.z());
    }

    void PlayerController::set_position(glm::vec3 position)
    {
        btTransform trans(m_ghost_object->getWorldTransform());
        trans.setOrigin(btVector3(position.x, position.y, position.z));
        m_ghost_object->setWorldTransform(trans);
    }

    glm::quat PlayerController::get_orientation() const
    {
        btQuaternion quat(m_ghost_object->getWorldTransform().getRotation());
        return glm::quat(quat.w(), quat.x(), quat.y(), quat.z());
    }

    glm::vec3 PlayerController::get_direction() const
    {
        btScalar matrix[16];
        m_ghost_object->getWorldTransform().getOpenGLMatrix(matrix);
        return glm::vec3(matrix[8], matrix[9], matrix[10]);
    }

    GLfloat PlayerController::get_yaw() const
    {
        btScalar matrix[16];
        m_ghost_object->getWorldTransform().getOpenGLMatrix(matrix);
        return glm::degrees(btAtan2(matrix[10], matrix[8]));
    }

    GLfloat PlayerController::get_pitch() const
    {
        btScalar matrix[16];
        m_ghost_object->getWorldTransform().getOpenGLMatrix(matrix);
        return glm::degrees(btAsin(-matrix[9]));
    }

    GLfloat PlayerController::get_roll() const
    {
        btScalar matrix[16];
        m_ghost_object->getWorldTransform().getOpenGLMatrix(matrix);
        return glm::degrees(btAtan2(matrix[9], matrix[8]));
    }

    GLfloat PlayerController::get_width() const
    {
        return m_width;
    }

    GLfloat PlayerController::get_height() const
    {
        return m_height;
    }

    GLfloat PlayerController::get_depth() const
    {
        return m_depth;
    }

    bool PlayerController::is_on_floor() const
    {
        return m_on_floor;
    }

    bool PlayerController::is_moving() const
    {
        return m_directions != STOP;
    }
}
