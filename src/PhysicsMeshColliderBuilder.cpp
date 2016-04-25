#include "PhysicsMeshColliderBuilder.hpp"

PhysicsMeshColliderBuilder::PhysicsMeshColliderBuilder(std::string path)
    : _model(Larp::Model::create(path)),
      _rotation(0.0, 0.0, 0.0, 1.0),
      _position(0.0, 0.0, 0.0),
      _mass(0.0),
      _local_inertia(0.0, 0.0, 0.0),
      _restitution(1.0),
      _user_pointer(nullptr)
{
}

void PhysicsMeshColliderBuilder::set_rotation(btQuaternion rotation)
{
    this->_rotation = rotation;
}

void PhysicsMeshColliderBuilder::set_position(btVector3 position)
{
    this->_position = position;
}

void PhysicsMeshColliderBuilder::set_mass(btScalar mass)
{
    this->_mass = mass;
}

void PhysicsMeshColliderBuilder::set_local_inertia(btVector3 local_inertia)
{
    this->_local_inertia = local_inertia;
}

void PhysicsMeshColliderBuilder::set_restitution(btScalar restitution)
{
    this->_restitution = restitution;
}

void PhysicsMeshColliderBuilder::set_user_pointer(void * user_pointer)
{
    this->_user_pointer = user_pointer;
}

PhysicsMeshColliderPtr PhysicsMeshColliderBuilder::build()
{
    return new PhysicsMeshCollider(_model, _rotation, _position, _mass, _local_inertia,
                                   _restitution, _user_pointer);
}
