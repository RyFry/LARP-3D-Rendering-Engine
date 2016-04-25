#include "PhysicsMeshColliderBuilder.cpp"

PhysicsMeshColliderBuilder::PhysicsMeshColliderBuilder(std::string path)
	: _mass(0.0),
	  _restitution(1.0)
{
    this->_model = Larp::Model::create(path);
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

void PhysicsMeshColliderBuilder::set_local_inertia(btScalar local_inertia)
{
    this->_local_inertia = local_inertia;
}

void PhysicsMeshColliderBuilder::set_restitution(btScalar restitution)
{
    this->_restitution = restitution;
}

PhysicsMeshColliderPtr PhysicsMeshColliderBuilder::build()
{
    return new PhysicsMeshColliderPtr(_model,
                                      _rotation,
                                      _position,
                                      _mass,
                                      _local_inertia,
                                      _restitution);
}
