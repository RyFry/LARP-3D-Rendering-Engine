#include "PhysicsObjectBuilder.hpp"

PhysicsObjectBuilder::PhysicsObjectBuilder()
    : _orientation(0.0, 0.0, 0.0, 1.0),
      _position(0.0, 0.0, 0.0),
      _mass(0.0),
      _local_inertia(0.0, 0.0, 0.0),
      _restitution(1.0),
      _user_pointer(nullptr)
{
}

void PhysicsObjectBuilder::set_orientation(glm::quat orientation)
{
    this->_orientation.x = orientation.x;
    this->_orientation.y = orientation.y;
    this->_orientation.z = orientation.z;
    this->_orientation.w = orientation.w;
}

void PhysicsObjectBuilder::set_position(glm::vec3 position)
{
    this->_position.x = position.x;
    this->_position.y = position.y;
    this->_position.z = position.z;
}

void PhysicsObjectBuilder::set_mass(GLfloat mass)
{
    this->_mass = mass;
}

void PhysicsObjectBuilder::set_local_inertia(glm::vec3 local_inertia)
{
    this->_local_inertia.x = local_inertia.x;
    this->_local_inertia.y = local_inertia.y;
    this->_local_inertia.z = local_inertia.z;
}

void PhysicsObjectBuilder::set_restitution(GLfloat restitution)
{
    this->_restitution = restitution;
}

void PhysicsObjectBuilder::set_user_pointer(Larp::NodePtr user_pointer)
{
    this->_user_pointer = user_pointer;
}

PhysicsObjectPtr PhysicsObjectBuilder::build()
{
    return new PhysicsObject(_orientation, _position, _mass, _local_inertia,
                             _restitution, _user_pointer);
}
