#include "PhysicsPlayerController.hpp"

PhysicsPlayerController::PhysicsPlayerController(PhysicsWorld* physics_world, btVector3 initial_position, 
    btScalar fwdspeed, btScalar bwdspeed, btScalar strspeed, btScalar jmpheight)
    :_forward_speed(fwdspeed),
    _backward_speed(bwdspeed),
    _strafe_speed(strspeed),
    _jump_height(jmpheight)
{
    // Create player shape
    btBoxShape* player_shape = new btBoxShape(btVector3(0.4, 0.8, 0.4));

    // Init player ghost object
    this->_ghost_object = new btPairCachingGhostObject();
    this->_transform = this->_ghost_object->getWorldTransform();
    this->_transform.setOrigin(initial_position);

    this->_ghost_object->setWorldTransform(this->_transform);

    // Set the shape and collision object type
    this->_ghost_object->setCollisionShape(player_shape);
    this->_ghost_object->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

    // Setup the character controller and add it to the physics world
    this->_char_controller =
        new btKinematicCharacterController(this->_ghost_object, player_shape, 1.0);
    physics_world->get_dynamics_world()->addCollisionObject(
        this->_ghost_object,
        btBroadphaseProxy::CharacterFilter,
        btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);
    physics_world->get_dynamics_world()->addAction(this->_char_controller);
}

void PhysicsPlayerController::update_movement(PhysicsWorld* world, PhysicsPlayerController::PlayerDirection direction)
{
    // For finding movement vectors:
    //   forward X up = right
    //   up X forward = left
    /*
    And the great thing about transformation matrices, is that this 3x3 rotation sub-matrix itself consists of three normalized vectors.
    Turns out, the first column is the vector pointing to the right (positive X axis). 
    The column to the right of that is the 'up vector' (positive Y). 
    The column next to that, is the vector pointing rearward or forward depending on your camera orientation convention (positive Z axis).
    https://www.opengl.org/discussion_boards/showthread.php/175515-Get-Direction-from-Transformation-Matrix-or-Quat
    */

    if (direction == PlayerDirection::STOP)
    {
        _char_controller->setWalkDirection(btVector3(0, 0, 0));
    }
    if (direction == PlayerDirection::FORWARD)
    {
        btVector3 forward(_ghost_object->getWorldTransform().getRotation() * btVector3(0, 0, _forward_speed));
        _char_controller->setWalkDirection(forward.safeNormalize());
    }
    else if (direction == PlayerDirection::BACKWARD)
    {
        btVector3 forward(_ghost_object->getWorldTransform().getRotation() * btVector3(0, 0, _backward_speed));
        _char_controller->setWalkDirection(-(forward.safeNormalize()));
    }
    else if (direction == PlayerDirection::LEFT)
    {
        btVector3 forward(_ghost_object->getWorldTransform().getRotation() * btVector3(0, 0, _strafe_speed));
        btVector3 left = btVector3(0, 1, 0).cross(forward).safeNormalize();
        _char_controller->setWalkDirection(left);
    }
    else if (direction == PlayerDirection::RIGHT)
    {
        btVector3 forward(_ghost_object->getWorldTransform().getRotation() * btVector3(0, 0, _strafe_speed));
        btVector3 right = forward.cross(btVector3(0, 1, 0)).safeNormalize();
        _char_controller->setWalkDirection(right);
    }
}

void PhysicsPlayerController::rotate(btScalar rotation_amount)
{
    btQuaternion(btVector3(0, 1, 0), rotation_amount);
}

void PhysicsPlayerController::jump()
{
    
}

void PhysicsPlayerController::set_user_pointer(void * user_pointer)
{
    this->_ghost_object->setUserPointer(user_pointer);
}

void PhysicsPlayerController::step(PhysicsWorld* world, btScalar delta_time)
{
    this->_char_controller->playerStep(world, delta_time);
}