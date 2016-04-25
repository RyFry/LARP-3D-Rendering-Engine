#include "PhysicsPlayerController.hpp"

PhysicsPlayerController::PhysicsPlayerController(PhysicsWorld* physics_world, btVector3 initial_position)
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

void PhysicsPlayerController::move(PhysicsWorld* world, btScalar delta_time, PhysicsPlayerController::PlayerDirection direction)
{
    // For finding movement vectors:
    //   forward X up = right
    //   up X forward = left

    if (direction == BACKWARD)
    {
        btVector3 forward(_ghost_object->getWorldTransform().getRotation() * btVector3(0, 0, 1));
        _char_controller->setWalkDirection(-(forward.safeNormalize()));
    }
    else if (direction == RIGHT)
    {
        btVector3 forward(_ghost_object->getWorldTransform().getRotation() * btVector3(0, 0, 1));
        btVector3 right = forward.cross(btVector3(0, 1, 0)).safeNormalize();
        _char_controller->setWalkDirection(right);
    }
    else if (direction == LEFT)
    {
        btVector3 forward(_ghost_object->getWorldTransform().getRotation() * btVector3(0, 0, 1));
        btVector3 left = btVector3(0, 1, 0).cross(forward).safeNormalize();
        _char_controller->setWalkDirection(left);
    }
    // _char_controller->playerStep();
    // _char_controller->setWalkDirection();

    _char_controller->playerStep(world->get_dynamics_world(), delta_time);
}

void PhysicsPlayerController::rotate(btScalar rotation_amount)
{
    
}
